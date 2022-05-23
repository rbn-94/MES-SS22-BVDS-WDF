clear all
close all
clc

signal = [1; zeros(64000,1)]'; % Impuls

[ytp, yhp]=wdf19deg(signal);


figure(1)
freqz(ytp(1:10000),1,10000)
title('WDF 19. Grades Tiefpass')

figure(2)
freqz(yhp(1:10000),1,10000)
title('WDF 19. Grades Hochpass')

[htp,wtp] = freqz(ytp(1:10000),1,10000);
[hhp,whp] = freqz(yhp(1:10000),1,10000);
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



%% wdf 19. Degree
function [y1, y2] = wdf19deg(signal)
xo= circshift(signal,1);
xo(1)=0;
xu = signal;


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


xo1=cross(xo,a1);  
xo2=adaptor(xo1,a2);
xo3=adaptor(xo2,a3);
xo4=adaptor(xo3,a4);



xu1= cross(xu,a5);
xu2= cross(xu1,a6);
xu3= adaptor(xu2,a7);
xu4= adaptor(xu3,a8);
xu5= adaptor(xu4,a9);

y1= (xo4 +xu5)*0.5;

y2= (-xo4 +xu5).*0.5;
end


%% Cross Adaptor
function [y] = cross(xo, a)

xt = zeros(4, 1);
y = zeros(length(xo), 1);


for i = 1 : length(xo)

xt = circshift(xt, 1);
xt(1) = ((-1)*xo(i)+xt(3))*a+(xt(3)*-1)+((-1)*xo(i)+xt(3));
y(i) = ((-1)*xo(i)+xt(3))*a+(xt(3)*-1);
end

end

%% Adaptor
function [y] = adaptor(xo, a)

xt = zeros(4, 1);
y = zeros(length(xo), 1);

for i = 1 : length(xo)

xt = circshift(xt, 1);

xt(1) = ((-1)*xo(i)+xt(3))*a+(xt(3)*-1);
y(i)=((xo(i)*(-1)+xt(3))*(-1))+((xo(i)*(-1)+xt(3))*a)+((-1)*xt(3));
end

end