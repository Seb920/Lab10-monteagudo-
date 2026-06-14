#!/bin/bash
archivo="diagnostico.txt"

{
echo "===== DIAGNOSTICO DEL SISTEMA ====="
echo "Fecha y hora: $(date)"
echo ""
echo "--- MEMORIA ---"
echo "Memoria total:  $(free -h | awk '/Mem:/ {print $2}')"
echo "Memoria usada:  $(free -h | awk '/Mem:/ {print $3}')"
echo "Memoria libre:  $(free -h | awk '/Mem:/ {print $4}')"
echo "Memoria Swap:   $(free -h | awk '/Swap:/ {print $2}')"
echo ""
echo "--- CPU ---"
top -bn1 | grep "Cpu(s)" | awk '{print "Uso CPU: " $2 "%"}'
echo ""
echo "--- TIEMPO ENCENDIDO ---"
uptime -p
echo ""
echo "--- TOP 10 PROCESOS POR MEMORIA ---"
ps aux --sort=-%mem | head -11
} > $archivo

echo "Reporte guardado en $archivo"
cat $archivo
