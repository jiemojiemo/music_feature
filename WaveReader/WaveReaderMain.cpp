#include "WaveReader.h"
using namespace std;

int main(int argc, const char * argv[])
{
	WaveReader wave("C:\\Users\\asus\\Desktop\\music\\quiet\\wav\\²»Öª - ·ÉÔ¶.wav");
	wave.Setup();
	//compute and play the file duration in seconds
	WAV_header hdr = wave.GetHeader();
	int samples = hdr.data.sub_chunk_2_size / ((hdr.fmt.bits_per_sample / 8)*hdr.fmt.channels);
	double seconds = (double)samples / (double)hdr.fmt.sample_rate;
	std::cerr << "file duration (seconds): " << seconds << std::endl;
	return 0;
}
