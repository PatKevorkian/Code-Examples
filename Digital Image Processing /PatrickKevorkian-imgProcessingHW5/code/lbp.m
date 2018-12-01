

wood = rgb2gray(imread('/Users/PatrickKevorkian/Desktop/wood.jpg'));

grass = rgb2gray(imread('/Users/PatrickKevorkian/Desktop/grass.jpg'));
%% 
% Display the images.
figure
imshow(wood)
title('wood')


figure
imshow(grass)
title('grass')
%%
% Extract LBP features from the images to encode their texture information.
lbpWood = extractLBPFeatures(wood,'Upright',false);

lbpGrass = extractLBPFeatures(grass,'Upright',false); 
%%

woodVsGrass = (lbpWood - lbpGrass).^2;
grassVsGrass = (lbpGrass - lbpGrass).^2;

figure
bar([woodVsGrass; grassVsGrass]','grouped')
title('Squared Error of LBP Histograms')
xlabel('LBP Histogram Bins')
legend('Wood vs Grass','Grass vs Grass')
