function res=DFT_nik(signal)
    signal=double(signal);

    l=size(signal,1);   
    x=[1:l];

    [x, u]=meshgrid(x,x);

  
    pre_dft=exp(1i*(-2*pi)./l); 

    
    pre_dft=(pre_dft.^((u-1).*(x-1))); 

  
    post_dft = pre_dft.'; 

    res = pre_dft*signal*post_dft;
end

