/**
*	@file main.cpp
*	@class main
*	
*	@author Chad R. Befus, Chris Sanden, Cody Rioux
*	@version 0.1.3:Bravo
*
*	License
*	-----------
*	Copyright (c) 2010 Chad R. Befus, Chris Sanden
*	
*	CAMEL (Content-based Audio and Music Extraction Library) is unrestricted, open 
*	source "software", with respect, but not limited, to modification, use, 
*	publishing, and distribution, subject to the following conditions:
*	
*	1. This copyright notice is maintained in its current form throughout CAMEL.
*	
*	2. Any publication or distribution credits the usage of CAMEL appropriately.
*	
*	This software is provided "as is" without warranty. The authors are in no way
*	liable for any misuse or damages arising from the use, modification or 
*	distribution of it or any part thereof.
*
*	Description
*	-----------
*	@brief the default main file -- extract segments/features from a set of passed in values
*
*	
*	Given PCM ASCII text file name, An integer corresponding to a feature type, An integer
*	correspoding to a segmentation type, An integer corresponding to the number of desired
*	segments, and a text file name for output, this code segments the PCM data, extracts
*	the features and outputs the results to the file. 
*
*	Required Dependencies
*	-----------
*	std::vector
*	std::string
*	std::cstdlib
*	std::iostream
*	std::sstream
*	std::fstream
*	segmenter.h
*
*	Example Usage
*	-----------
*	~$ featExtract samplePCM.txt 1 2 10 output.txt
*
*
*	More examples to be found in example folder
*
*	@todo
*	
*
**/


#include <cstdlib>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>

#include "src/segmenter.h"

using namespace std;

/**
*	get domain for a window data
**/
void DomainTest()
{
	Domain domain;
	domain.setFileName("samplePCM.txt");
	domain.setup();
	domain.setWindowSize(1024);
	domain.setStartPosition(0);
	domain.setEndPosition(10000);
	vector<double> domainVec = domain.getFrequencyDomainWindow(0);
	cout << domainVec.size();
	for (int i = 0; i < 102; ++i) {
		cout << 44100.0/1024 * i << ":"<<domainVec[i] << endl;
	}
	
}

void MainTest(int argc, char *argv[])
{
	/*
	*/
	//get the string name of the PCM file
	string strFileName = argv[1];	//samplePCM.txt

									//get the string feature type and convert to an int
	string strFeatureType = argv[2];	//1
	int intFeatureType = 0;
	stringstream ssFeatureType(strFeatureType);
	ssFeatureType >> intFeatureType;

	//get the string segment type and convert to an int
	string strSegmentType = argv[3];	//2
	int intSegmentType = 0;
	stringstream ssSegmentType(strSegmentType);
	ssSegmentType >> intSegmentType;

	//get the string number of segments desired and convert to an int
	string strNumSegments = argv[4];	//10
	int intNumSegments = 0;
	stringstream ssNumSegments(strNumSegments);
	ssNumSegments >> intNumSegments;

	//get the string output file name
	string strOutFileName = argv[5];	//output.txt

										//do the segmentation / feature extraction... simple right!?!
	Segmenter segProcess(strFileName);
	segProcess.setup();
	segProcess.run(intFeatureType, intSegmentType, intNumSegments);
	vector< vector<double> > vvdFeatResults = segProcess.getFeatureResults();
	vector<int> vviPosResults = segProcess.getPositionResults();

	//create the output file and output the data in some format
	ofstream fout(strOutFileName.c_str());
	fout << strOutFileName << endl;
	for (int i = 0; i < vvdFeatResults.size(); ++i) {
		fout << i << ": " << vviPosResults[i] << " -> " << vviPosResults[i + 1];
		fout << " = " << vviPosResults[i + 1] - vviPosResults[i] << " >> ";
		for (int j = 0; j < vvdFeatResults[i].size(); ++j) {
			fout << vvdFeatResults[i][j] << " -- ";
		}
		fout << endl;
	}

	fout.close();
	
}

/**
*	just read data from file
**/
void FileVectorTest()
{
	int vecStart = 0;
	int vecEnd = 100;
	FileVector<int> p;
	p.setFileName("samplePCM.txt");
	p.setup();
	for (int i = vecStart; i < p.size() && i < vecEnd; ++i)
		cout << p[i] << endl;
}


void FeatureTest()
{
	Domain domain;
	domain.setFileName("samplePCM.txt");
	domain.setup();
	domain.setWindowSize(1024);
	domain.setStartPosition(0);
	domain.setEndPosition(10000);
	vector<double> frequencyDomain = domain.getFrequencyDomainWindow(0);
	vector<int> timeDomain = domain.getTimeDomainWindow(0);

	Feature f;
	f.setWindowSize(1024);
	double value = f.calcWindowMean(timeDomain);
	cout << value << endl;


}

void FeatureExtractTest()
{
	FeatureExtract fe;
	fe.setFileName("samplePCM.txt");
	fe.setWindowSize(1024);
	fe.setup();
	fe.getFeature(0, 88200, 11);
	auto result = fe.getValues();
	cout << result.size() << endl;
	cout << result[0] << endl;
}
int main(int argc, char *argv[])
{
	//MainTest();
	//DomainTest();
	//FeatureTest();
	FeatureExtractTest();
	//FileVectorTest();

}


