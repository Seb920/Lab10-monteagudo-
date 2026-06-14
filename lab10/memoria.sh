#!/bin/bash
archivo="reporte_memoria.txt"
echo "REPORTE DE MEMORIA" > $archivo
date >> $archivo
echo "" >> $archivo
free -h >> $archivo
echo "" >> $archivo
ps aux --sort=-%mem | head -6 >> $archivo
echo "Reporte generado en $archivo"
