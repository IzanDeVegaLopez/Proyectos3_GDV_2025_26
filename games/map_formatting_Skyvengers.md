# Formato de mapas para Skyvengers

N // Número de giros (`uint`) <br>
A1 // Separación desde el último giro (`uint`) <br>
&nbsp;&nbsp;&nbsp;&nbsp;B1 // Dirección del giro (`char` - L o R) <br>
A2 B2 <br>
A3 B3 <br>
... <br>
AN BN <br>

M // Número de obstáculos (`uint`) <br>
X1 Y1 // Coordenadas del obstáculo (`std::pair<int,int>`) <br>
X2 Y2 <br>
X3 Y3 <br>
... <br>
XM BM <br>

