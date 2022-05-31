clear all
close all
clc

%%
signal = [1; zeros(64000,1)]'; % Impuls

%%
% signal=audioread("piano2.wav");

%%
%weights
alpha0=1;
alpha1=1;
alpha2=1;
alpha3=1;
alpha4=1;
alpha5=1;
alpha6=1;
alpha7=1;
alpha8=1;


%filter cascaded low-pass-outputs
[ytp, yhp]=wdf19deg(signal,1);     % 1. Filter
[ytp1, yhp1]=wdf19deg(ytp,2);      % 2. Filter
[ytp2, yhp2]=wdf19deg(ytp1,4);     % 3. Filter
[ytp3, yhp3]=wdf19deg(ytp2,8);     % 4. Filter
[ytp4, yhp4]=wdf19deg(ytp3,16);    % 5. Filter
[ytp5, yhp5]=wdf19deg(ytp4,32);    % 6. Filter
[ytp6, yhp6]=wdf19deg(ytp5,64);    % 7. Filter
[ytp7, yhp7]=wdf19deg(ytp6,128);   % 8. Filter


% calc delays
d0 = 4; % initial delay length

d7 = 2^7 * d0;
d6 = d7 + 2^6*d0;
d5 = d6 + 2^5*d0;
d4 = d5 + 2^4*d0;
d3 = d4 + 2^3*d0;
d2 = d3 + 2^2*d0;
d1 = d2 + 2^1*d0;

delayS1=delay(yhp, d1);
delayS2=delay(yhp1, d2);
delayS3=delay(yhp2, d3);
delayS4=delay(yhp3, d4);
delayS5=delay(yhp4, d5);
delayS6=delay(yhp5, d6);
delayS7=delay(yhp6, d7);



%sum of all filter outputs --> output of octave filter
b_out=(yhp.*alpha0)+(yhp1.*alpha1)+(yhp2.*alpha2)+(yhp3.*alpha3)+(yhp4.*alpha4)+(yhp5.*alpha5)+(yhp6.*alpha6)+(yhp7.*alpha7)+(ytp7.*alpha8);

%sum of all filter outputs with delays --> output of octave filter
b_out_with_delays=(delayS1.*alpha0)+(delayS2.*alpha1)+(delayS3.*alpha2)+(delayS4.*alpha3)+(delayS5.*alpha4)+(delayS6.*alpha5)+(delayS7.*alpha6)+(yhp7.*alpha7)+(ytp7.*alpha8);


%%
figure(1)
freqz(ytp(1:10000),1,10000)
title('WDF 19. Grades Tiefpass')
%%
figure(2)
freqz(yhp(1:10000),1,10000)
title('WDF 19. Grades Hochpass')

%%
[htp,wtp] = freqz(ytp(1:64000),1,64000);
[hhp,whp] = freqz(yhp(1:64000),1,64000);
figure(3)
plot(wtp/pi,20*log10(abs(htp)))
hold on;
plot(whp/pi,20*log10(abs(hhp)))
grid minor;
ax = gca;
ax.YLim = [-100 20];
ax.XTick = 0:.5:2;
xlabel('Normalized Frequency (\times\pi rad/sample)')
ylabel('Magnitude (dB)')
legend('Tiefpass','Hochpass')

%%
figure(4)
freqz(ytp(1:64000),1,64000)
hold on
freqz(ytp1(1:64000),1,64000)
freqz(ytp2(1:64000),1,64000)
freqz(ytp3(1:64000),1,64000)
freqz(ytp4(1:64000),1,64000)
freqz(ytp5(1:64000),1,64000)
freqz(ytp6(1:64000),1,10000)
freqz(ytp7(1:64000),1,64000)
title('WDF 19. Grades Tiefpass')
%%
%plot of every cascaded filter

[htp,wtp] = freqz(ytp(1:64000),1,64000);
hold on;
[hhp,whp] = freqz(yhp(1:64000),1,64000);
[htp1,wtp1] = freqz(ytp1(1:64000),1,64000);
[hhp1,whp1] = freqz(yhp1(1:64000),1,64000);
[htp2,wtp2] = freqz(ytp2(1:64000),1,64000);
[hhp2,whp2] = freqz(yhp2(1:64000),1,64000);
[htp3,wtp3] = freqz(ytp3(1:64000),1,64000);
[hhp3,whp3] = freqz(yhp3(1:64000),1,64000);
[htp4,wtp4] = freqz(ytp4(1:64000),1,64000);
[hhp4,whp4] = freqz(yhp4(1:64000),1,64000);
[htp5,wtp5] = freqz(ytp5(1:64000),1,64000);
[hhp5,whp5] = freqz(yhp5(1:64000),1,64000);
[htp6,wtp6] = freqz(ytp6(1:64000),1,64000);
[hhp6,whp6] = freqz(yhp6(1:64000),1,64000);
[htp7,wtp7] = freqz(ytp7(1:64000),1,64000);
[hhp7,whp7] = freqz(yhp7(1:64000),1,64000);
figure(5) ;
plot(wtp/pi,20*log10(abs(htp)))
hold on;
plot(whp/pi,20*log10(abs(htp1)))
plot(whp/pi,20*log10(abs(htp2)))
plot(whp/pi,20*log10(abs(htp3)))
plot(whp/pi,20*log10(abs(htp4)))
plot(whp/pi,20*log10(abs(htp5)))
plot(whp/pi,20*log10(abs(htp6)))
plot(whp/pi,20*log10(abs(htp7)))
grid minor;
ax = gca;
ax.YLim = [-100 20];
ax.XTick = 0:.5:2;
xlabel('Normalized Frequency (\times\pi rad/sample)')
ylabel('Magnitude (dB)')
legend('1. Filter','2. Filter','3. Filter','4. Filter','5. Filter','6. Filter','7. Filter','8. Filter')

%plot of final output without delays
figure(6)
freqz(b_out(1:64000),1,64000)
title('Output filterbank')

%plot of final output with delays
figure(7)
freqz(b_out_with_delays(1:64000),1,64000)
title('Output filterbank')

%%
audiowrite("out_piano2.wav",b_out,48000 );


%% wdf 19. Degree
function [y1, y2] = wdf19deg(signal,n) %ouput: y1:low-Fass y2:high-pass Input:signal, number of delays
xo= circshift(signal,n);

for i=1:n
xo(i)=0;
end
xu = signal;

n=n*2;

% coefficients

a1=-0.226119;
a2=0.397578;
a3=0.160677;
a4=0.049153;
a5=-0.063978;
a6=-0.423068;
a7=0.258673;
a8=0.094433;
a9=0.015279;


xo1=cross(xo,a1,n);  
xo2=adaptor(xo1,a2,n);
xo3=adaptor(xo2,a3,n);
xo4=adaptor(xo3,a4,n);



xu1= cross(xu,a5,n);
xu2= cross(xu1,a6,n);
xu3= adaptor(xu2,a7,n);
xu4= adaptor(xu3,a8,n);
xu5= adaptor(xu4,a9,n);

y1= (xo4 +xu5)*0.5;

y2= (-xo4 +xu5).*0.5;
end


%% Cross Adaptor
function [y] = cross(xo, a, n) %Output y of cross adaptor Input: inputvector, coefficient, number of delays

xt = zeros(1000, 1);
y = zeros(length(xo), 1);


for i = 1 : length(xo)

xt = circshift(xt, 1);
xt(1) = ((-1)*xo(i)+xt(1+n))*a+(xt(1+n)*-1)+((-1)*xo(i)+xt(1+n));
y(i) = ((-1)*xo(i)+xt(1+n))*a+(xt(1+n)*-1);
end

end

%% Adaptor
function [y] = adaptor(xo, a, n) %Output y of cross adaptor Input: inputvector, coefficient, number of delays

xt = zeros(1000, 1);
y = zeros(length(xo), 1);

for i = 1 : length(xo)

xt = circshift(xt, 1);

xt(1) = ((-1)*xo(i)+xt(1+n))*a+(xt(1+n)*-1);
y(i)=((xo(i)*(-1)+xt(1+n))*(-1))+((xo(i)*(-1)+xt(1+n))*a)+((-1)*xt(1+n));
end

end

%% Delay
function [y]= delay(x,n)

xt = zeros(round(n)+1, 1);
y = zeros(length(x), 1);
for i = 1 : length(x)
xt = circshift(xt, 1);
xt(1)=x(i);
y(i)=xt(round(n)+1);
end
end