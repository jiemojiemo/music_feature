#include "WaveSegmenter.h"
#include "WaveFileSegmenter.h"
#include <iostream>
#include <sstream>
using namespace std;

void LoopSegment( const string& filePaht );
string int2string( int x );
int main()
{
	string filePath("C:\\Users\\asus\\Desktop\\music\\quiet\\wav\\不知 - 飞远.wav");
	LoopSegment(filePath);
	//string filePath("C:\\Users\\asus\\Desktop\\music\\quiet\\wav\\不知 - 飞远.wav");
	//WaveFileSegmenter fileSegment(filePath);
	//fileSegment.Setup();
	//fileSegment.doSegment(0, 10);
	//double duration = fileSegment.GetSourceFileDuration();
	//cout << duration << endl;
	//WaveSegmenter s("C:\\Users\\asus\\Desktop\\music\\quiet\\wav\\不知 - 飞远.wav");
	//s.Setup();
	//s.GetMonoSegment(0.0, 10.0);
}

void LoopSegment(const string& filePath)
{
	WaveFileSegmenter fileSegment(filePath);
	fileSegment.Setup();
	double duration = fileSegment.GetSourceFileDuration();

	double ignoreBeg = 30.0;
	double ignoreEnd = 30.0;
	double segmentTime = 30.0;
	double timeBeg = ignoreBeg;
	double timeEnd = duration - ignoreEnd;
	
	if (timeBeg + segmentTime > timeEnd)
	{
		cout << "music is to short to segment" << endl;
	}
	int segmentCount = (timeEnd - timeBeg) / segmentTime;
	int count = 0;
	do 
	{
		string segmentName( filePath.begin(),filePath.end() - 4);
		segmentName += int2string(count);
		segmentName += ".wav";

		fileSegment.doSegment(timeBeg, timeBeg + segmentTime, segmentName);
		timeBeg += segmentTime;
	} while (++count < segmentCount);
}

string int2string(int x)
{
	stringstream stream;
	string stringX;
	stream << x;
	stringX = stream.str();
	return stringX;
}