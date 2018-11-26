s = serial('COM10', ...
            'BaudRate', 115200);
        
fopen(s);
L = 5000;
u1 = zeros(1, L);
u2 = zeros(1, L);
M = [];

for i = 1:L
    %measurement = fscanf(s);
    if (s.BytesAvailable > 0)
        measurement = fread(s, s.BytesAvailable, 'uint8');
        M = [M; measurement];
    end
end

fclose(s);
delete(s);
clear s

%%
i = 1;
for idx = 1:(length(M)-7)
    if (M(idx) == 's' && M(idx + 1) == 't' && M(idx + 2) == 'r')
        u1(i) = uint16(M(idx + 3)) + uint16(256) * uint16(M(idx + 4));
        u2(i) = uint16(M(idx + 5)) + uint16(256) * uint16(M(idx + 6));
        i = i + 1;
    else
    end
end

u1 = double(u1) / 4096;
u2 = double(u2) / 4096;

%% Plot
figure;
grid on; hold on;
plot(u1);
plot(u2);
