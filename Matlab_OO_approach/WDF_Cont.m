classdef WDF_Cont < handle
    %UNTITLED Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        n
        xt_a
        ad1
        ad2
        ad3
        ad4
        ad5
        ad6
        ad7
        ad8
        ad9
    end
    
    methods
        function obj = WDF_Cont(delay)
            %UNTITLED Construct an instance of this class
            %   Detailed explanation goes here
            obj.xt_a = zeros(delay+1, 1);
            obj.n = delay;
            a1=-0.226119;
            a2=0.397578;
            a3=0.160677;
            a4=0.049153;
            a5=-0.063978;
            a6=-0.423068;
            a7=0.258673;
            a8=0.094433;
            a9=0.015279;
            obj.ad1 = Adaptors(delay+1, a1);
            obj.ad2 = Adaptors(delay+1, a2);
            obj.ad3 = Adaptors(delay+1, a3);
            obj.ad4 = Adaptors(delay+1, a4);
            obj.ad5 = Adaptors(delay+1, a5);
            obj.ad6 = Adaptors(delay+1, a6);
            obj.ad7 = Adaptors(delay+1, a7);         
            obj.ad8 = Adaptors(delay+1, a8);
            obj.ad9 = Adaptors(delay+1, a9);          
        end
       
        function [y1, y2] = calc(obj,x)
            %METHOD1 Summary of this method goes here
            %   Detailed explanation goes here
            obj.xt_a = circshift(obj.xt_a, 1);
            obj.xt_a(1) = x;
            xo = obj.xt_a(1+obj.n);
            xu = x;
            xo1=obj.ad1.calc_cross(xo);
            xo2=obj.ad2.calc(xo1);
            xo3=obj.ad3.calc(xo2);
            xo4=obj.ad4.calc(xo3);


            xu1=obj.ad5.calc_cross(xu);
            xu2=obj.ad6.calc_cross(xu1);
            xu3=obj.ad7.calc(xu2);
            xu4=obj.ad8.calc(xu3);
            xu5=obj.ad9.calc(xu4);
            y1= (xo4 +xu5)*0.5;
            y2= (-xo4 +xu5).*0.5;
        end
    end
end

