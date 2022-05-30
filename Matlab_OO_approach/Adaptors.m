classdef Adaptors < handle
    %UNTITLED Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        xt 
        n
        a
    end
    
    methods
        function obj = Adaptors(delay, gamma)
                obj.n = delay;
                obj.xt = zeros(obj.n+2, 1);
                obj.a = gamma;
        end
        function [y] = calc(obj,xo)
        
        obj.xt = circshift(obj.xt, 1);
        
        obj.xt(1) = ((-1)*xo+obj.xt(obj.n+1))*obj.a+(obj.xt(obj.n+1)*-1);
        y=((xo*(-1)+obj.xt(obj.n+1))*(-1))+((xo*(-1)+obj.xt(obj.n+1))*obj.a)+((-1)*obj.xt(obj.n+1));
        end
        function [y] = calc_cross(obj,xo)
        
        obj.xt = circshift(obj.xt, 1);
        
        obj.xt(1) = ((-1)*xo+obj.xt(obj.n+1))*obj.a+(obj.xt(obj.n+1)*-1)+((-1)*xo+obj.xt(obj.n+1));
        y = ((-1)*xo+obj.xt(obj.n+1))*obj.a+(obj.xt(obj.n+1)*-1);
        end        
    end
end

