#!/bin/bash
uso=$(free | awk '/Mem:/ {printf "%.0f", $3/$2 * 100}')
echo "Uso actual de memoria: $uso%"
if [ $uso -gt 80 ]; then
    echo "ALERTA: El uso de memoria supera el 80% ($uso%)"
else
    echo "Memoria en niveles normales ($uso%)"
fi
