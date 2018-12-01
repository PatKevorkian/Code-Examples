me = rgb2gray(imread('/Users/PatrickKevorkian/Desktop/me.jpg'));
meGlcms = graycomatrix(me);
stats = graycoprops(meGlcms);

