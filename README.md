# Temperature-fluctuation-of-heavy-ion-collisions

Wavelet analysis is used for temperature fluctuations

## Signal Production

I have used UrQMD data generator for the data. In Data folder pt.C file can be used to extract Pt histograms in multiple bins.

## Analysis

Using normalization.c can be used to normalize the pt histograms and Tsallis fitting is used to extract temperature. 
* random generator is used to generate synthetic data and is used to extract paramter for wavelat analysis.
* Wavelet.py is used for the temperature fluctuation estimation.
* neural network contain wavelet neural network which can be used for estimating fluctuations.


## Efficiency

* study of efficiency of the proposed method, by varing number of anomalies
