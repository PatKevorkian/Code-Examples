function [digest,key] = phaseEncrypt(f)
fourier=fft2(f);
F_Phase = exp(1i*angle(fourier));

figure,imshow(F_Phase);

idx=randperm(numel(F_Phase)); 
shuffled_phase=reshape(F_Phase(idx),size(F_Phase));

figure,imshow(shuffled_phase);

digest= ifft2(abs(fourier).*shuffled_phase);

iidx(idx)=1:numel(F_Phase);
key = iidx;

f1=abs(digest);
fm=max(f1(:));
figure,imshow(f1/fm);
end