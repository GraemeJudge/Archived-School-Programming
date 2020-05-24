T = 0.1;
t = -0.5 : 0.001 : 0.5;
x = pi*t/T;
y = sin(x + eps)./(x + eps);
plot(t, y);