# Predicting Pulsar Star Prediction

- Pulsar stars are highly magnetized neutron stars or white dwarves that emit beams
of electromagnetic radiation, that is detectable here on Earth when the beam points
in our direction.

- In this project, I will explore machine learning methods that can be used to classify pulsar stars using the following attributes:
	
	1. Mean of integrated profile
	2. Standard deviation of integrated profile
	3. Skewness of the integrated profile
	4. Excess kurtosis of the integrated profile
	5. Mean of the DM-SNR curve
	6. Standard deviation of the DM-SNR curve
	7. Excess kurtosis of the DM-SNR curve
	8. Skewness of the DM-SNR curve

- Dataset contains 17898 samples
- From this dataset we can see that 16259 samples correspond to class 0
- From this dataset we can see that 1639 samples correspond to class 1

This application uses a logistic regression model to determine whether a neutron 
star is a pulsar star.

This logistic regrerssion model was made from scratch using numpy.

The testing accuracy achieved by this model is 98.9%.
