clear all
close all
clc


signal = [1; zeros(64000,1)]'; % Impuls
ytp = zeros(length(signal), 1);
yhp = zeros(length(signal), 1);
wdf = WDF_Cont(1);
for i=1:length(signal)
    [ytp(i), yhp(i)] = wdf.calc(signal(i));
end

%[ytp, yhp]=wdf19deg(signal);

figure(1)
freqz(ytp(1:10000),1,10000)
title('WDF 19. Grades')


