logA = T(imA,1);
imshow(logA);

function s = T(z,c) 
s = normc(c*log(1+double(z)));
end 