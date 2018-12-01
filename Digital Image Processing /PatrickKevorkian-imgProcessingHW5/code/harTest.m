  I = imread('/Users/PatrickKevorkian/Desktop/berk.jpg');

	%Get the co occurence matrix (in Matlab called GLCM: Gray Level Co 
  %Occurence Matrix)
  glcm = graycomatrix(I, 'offset', [0 1], 'Symmetric', true);

	%calculate feature 4 (Variance), 5 (Inverse Difference Moment) and 6 
  %(Sum Average)
  xFeatures = 1:14;
  x = haralickTextureFeatures(glcm, 1:14);

  %Get only the features you want
  x = x( xFeatures )