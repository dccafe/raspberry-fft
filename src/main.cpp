#include "../lib/fft/FFT.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

#define FFT_WINDOW_SIZE 1024   // Used also for buffer size
#define WAV_HEADER_SIZE 44     // In bytes

#define DEV
//#define DEBUG

using namespace std;

int main(int argc, char **argv)
{
  // Reading from terminal pipeline
  FILE* instream=fopen("/dev/stdin","r");
  
  // Using tmp as a buffer
  short *tmp = new short[FFT_WINDOW_SIZE];
  
  // Declaring a vector to store time samples
  vector<FFT::Complex> time_samples(FFT_WINDOW_SIZE,0);
  
  // Declaring magnitude vector
  double *magnitude = new double[FFT_WINDOW_SIZE];
  
  // Variable max is the temporary maximum frequency amplitude
  int max_index=0;
  double max=0;
  double volume=0;
  double frequency = 0;
  
  // Ignore the wav header 
  fread(tmp,WAV_HEADER_SIZE,1,instream);
  
  // Create an instance of the fft.
  FFT dft(FFT_WINDOW_SIZE);
  
  // Read N samples of 2 bytes (16-bit long) from the pipeline
  while( fread(tmp,FFT_WINDOW_SIZE,2,instream) )
  {
    // Copy all samples to the Complex Vector
    for(int i=0;i<FFT_WINDOW_SIZE;i++)
      time_samples[i] = tmp[i];
    
    // Apply the Fourier Transform
    vector<FFT::Complex> freq_samples = dft.transform(time_samples);
    
    // Get magnitude vector
    for(int i=0;i<FFT_WINDOW_SIZE;i++) 
      magnitude[i] = abs(freq_samples[i]);

    // Find the maximum (ignoring DC value, use only first half)
    for(int i=1;i< (FFT_WINDOW_SIZE >> 1);i++)
    {
      if(magnitude[i]>=max) 
      {
	volume+=magnitude[i];
        max=magnitude[i];
        max_index=i;
      }
    }
    
    // Decode the frequency
    frequency = max_index * 8000 / FFT_WINDOW_SIZE / 2 ;
    
    // Output : Show the detected frequency when there is some sound
    if(volume>5)
      cout << "Frequency decoded : " << frequency << endl;      
    
    // Reset values
    max = 0;   max_index = 0; volume = 0;
    
  }
  
  // Clean up the memory 
  delete[] tmp;
  fclose(instream);
}
