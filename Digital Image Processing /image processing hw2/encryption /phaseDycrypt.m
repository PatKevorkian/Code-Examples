function orig = phaseDycrypt(digest,key)
fourier=fft2(digest);
F_Phase = exp(1i*angle(fourier));

recovered_image=reshape(F_Phase(key),size(F_Phase));
orig=ifft2(abs(fourier).*recovered_image);

f1=abs(orig);
fm=max(f1(:));
figure,imshow(f1/fm);
end