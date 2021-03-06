clear all
close all
clc


signal = [1; zeros(64000,1)]'; % Impuls

[ytp, yhp]=wdf19deg(signal,1);     % 1. Filter
[ytp1, yhp1]=wdf19deg(signal,2);   % 2. Filter
[ytp2, yhp2]=wdf19deg(signal,4);   % 3. Filter
[ytp3, yhp3]=wdf19deg(signal,8);   % 4. Filter
[ytp4, yhp4]=wdf19deg(signal,16);  % 5. Filter
[ytp5, yhp5]=wdf19deg(signal,32);  % 6. Filter
[ytp6, yhp6]=wdf19deg(signal,64);  % 7. Filter
[ytp7, yhp7]=wdf19deg(signal,128);  % 8. Filter
[ytp8, yhp8]=wdf19deg(signal,256);  % 9. Filter


% figure(1)
% freqz(ytp(1:10000),1,10000)
% title('WDF 19. Grades Tiefpass')
% 
% figure(2)
% freqz(yhp(1:10000),1,10000)
% title('WDF 19. Grades Hochpass')
% 
% [htp,wtp] = freqz(ytp(1:10000),1,10000);
% [hhp,whp] = freqz(yhp(1:10000),1,10000);
% figure(3)
% plot(wtp/pi,20*log10(abs(htp)))
% hold on;
% plot(whp/pi,20*log10(abs(hhp)))
% grid minor;
% ax = gca;
% ax.YLim = [-100 20];
% ax.XTick = 0:.5:2;
% xlabel('Normalized Frequency (\times\pi rad/sample)')
% ylabel('Magnitude (dB)')
% legend('Tiefpass','Hochpass')

% figure(4)
% freqz(ytp(1:10000),1,10000)
% hold on
% freqz(ytp1(1:10000),1,10000)
% freqz(ytp2(1:10000),1,10000)
% title('WDF 19. Grades Tiefpass')



[htp,wtp] = freqz(ytp(1:10000),1,10000);
[hhp,whp] = freqz(yhp(1:10000),1,10000);
[htp1,wtp1] = freqz(ytp1(1:10000),1,10000);
[hhp1,whp1] = freqz(yhp1(1:10000),1,10000);
[htp2,wtp2] = freqz(ytp2(1:10000),1,10000);
[hhp2,whp2] = freqz(yhp2(1:10000),1,10000);
[htp3,wtp3] = freqz(ytp3(1:10000),1,10000);
[hhp3,whp3] = freqz(yhp3(1:10000),1,10000);
[htp4,wtp4] = freqz(ytp4(1:10000),1,10000);
[hhp4,whp4] = freqz(yhp4(1:10000),1,10000);
[htp5,wtp5] = freqz(ytp5(1:10000),1,10000);
[hhp5,whp5] = freqz(yhp5(1:10000),1,10000);
[htp6,wtp6] = freqz(ytp6(1:10000),1,10000);
[hhp6,whp6] = freqz(yhp6(1:10000),1,10000);
[htp7,wtp7] = freqz(ytp7(1:10000),1,10000);
[hhp7,whp7] = freqz(yhp7(1:10000),1,10000);
[htp8,wtp8] = freqz(ytp8(1:10000),1,10000);
[hhp8,whp8] = freqz(yhp8(1:10000),1,10000);


figure(3) ;
plot(wtp/pi,20*log10(abs(htp)))
hold on;
plot(whp/pi,20*log10(abs(htp1)))
plot(whp/pi,20*log10(abs(htp2)))
plot(whp/pi,20*log10(abs(htp3)))
plot(whp/pi,20*log10(abs(htp4)))
% plot(whp/pi,20*log10(abs(htp5)))
% plot(whp/pi,20*log10(abs(htp6)))
% plot(whp/pi,20*log10(abs(htp7)))
% plot(whp/pi,20*log10(abs(htp8)))

grid minor;
ax = gca;
ax.YLim = [-100 20];
ax.XTick = 0:.5:2;
xlabel('Normalized Frequency (\times\pi rad/sample)')
ylabel('Magnitude (dB)')
legend('1. Filter','2. Filter','3. Filter','4. Filter','5. Filter')

%% wdf 19. Degree
function [y1, y2] = wdf19deg(signal,n)
xo= circshift(signal,n);

for i=1:n
xo(i)=0;
end
xu = signal;

n=n*2;

% Koeffizienten

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
function [y] = cross(xo, a, n)

xt = zeros(1000, 1);
y = zeros(length(xo), 1);


for i = 1 : length(xo)

xt = circshift(xt, 1);
xt(1) = ((-1)*xo(i)+xt(1+n))*a+(xt(1+n)*-1)+((-1)*xo(i)+xt(1+n));
y(i) = ((-1)*xo(i)+xt(1+n))*a+(xt(1+n)*-1);
end

end

%% Adaptor
function [y] = adaptor(xo, a, n)

xt = zeros(1000, 1);
y = zeros(length(xo), 1);

for i = 1 : length(xo)

xt = circshift(xt, 1);

xt(1) = ((-1)*xo(i)+xt(1+n))*a+(xt(1+n)*-1);
y(i)=((xo(i)*(-1)+xt(1+n))*(-1))+((xo(i)*(-1)+xt(1+n))*a)+((-1)*xt(1+n));
end

end