#!/usr/bin/env bash

set -e

echo "====================================="
echo " Instalador de dependencias FIR UTN "
echo "====================================="

# =========================

# Detectar package manager

# =========================

if command -v pacman >/dev/null 2>&1; then
DISTRO="arch"
elif command -v apt >/dev/null 2>&1; then
DISTRO="debian"
elif command -v dnf >/dev/null 2>&1; then
DISTRO="fedora"
else
echo "❌ No se pudo detectar el package manager"
exit 1
fi

echo "✔ Detectado: $DISTRO"

# =========================

# Instalar dependencias sistema

# =========================

echo "=== Instalando dependencias del sistema ==="

if [ "$DISTRO" = "arch" ]; then
    sudo pacman -S --needed --noconfirm \
        python \
        python-pip \
        python-numpy \
        python-matplotlib \
        tk \
        alsa-utils

elif [ "$DISTRO" = "debian" ]; then
sudo apt update
sudo apt install -y \
python3 \
python3-pip \
python3-numpy \ 
python3-matplotlib \
python3-tk \
alsa-utils

elif [ "$DISTRO" = "fedora" ]; then
sudo dnf install -y \
python3 \
python3-pip \
python3-numpy \ 
python3-matplotlib \
python3-tkinter \
alsa-utils
fi

# =========================

# Instalar dependencias Python

# =========================

echo "=== Instalando dependencias Python ==="
if [ "$DISTRO" = "arch" ]; then
sudo pacman -S python-matplotlib python-numpy
else
pip3 install --user -r requirements.txt
fi
echo "=== Instalando tkinterdnd2 ==="
if [ "$DISTRO" = "arch" ]; then
sudo pacman -S --needed --noconfirm yay
yay -Sy tkdnd2-git
else
pip3 install --user tkinterdnd2
fi
# =========================

# Verificaciones

# =========================

echo "=== Verificando instalación ==="

if ! command -v aplay >/dev/null 2>&1; then
echo "⚠️ aplay no está disponible (audio puede no funcionar)"
else
echo "✔ aplay OK"
fi
cd code/utils/scripts/
echo "✔ Instalación completa"
echo "Podés ejecutar: ./fir_filter_utn -gui"
