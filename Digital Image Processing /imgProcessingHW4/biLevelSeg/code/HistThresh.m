originalImage = rgb2gray(write);
%originalImage = cameraman;
axis image; % Make sure image is not artificially stretched because of screen's aspect ratio.

% Just for fun, let's get its histogram and display it.
[pixelCount, grayLevels] = imhist(originalImage);
bar(pixelCount);
title('Histogram of original image');
xlim([0 grayLevels(end)]); % Scale x axis manually.
grid on;

%threshold for bi level thresholding 
%thresholdValue = 100;
%binaryImage = originalImage > thresholdValue; % Bright objects will be chosen if you use >.


%thresholding for multi level thresholding (3)
t1=20;
t2=170;
triImage = size(originalImage);
for J = 1 : size(originalImage,1)
  for K = 1 : size(originalImage,2)
     
    if originalImage(J,K) > t1 && originalImage(J,K) <= t2
        triImage(J,K) = 128;
    end
    if originalImage(J,K) > t2
        triImage(J,K) = 0;
    end
    if originalImage(J,K) <= t1
        triImage(J,K) = 256;
    end
     
  end
end
 


% Display the binary image.
% figure();
% imshow(binaryImage); 
% title('Binary Image, obtained by thresholding');

%Disply 3 shade image 
figure();
imshow(uint8(triImage));
title('Grey Image, obtained by thresholding');