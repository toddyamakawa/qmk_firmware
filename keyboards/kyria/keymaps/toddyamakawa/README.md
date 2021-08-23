

# Setup

```
sudo apt install -y git python3-pip
python3 -m pip install --user qmk
```

```
Ψ Found qmk_firmware at /home/todd/qmk_firmware.
Ψ QMK Doctor is checking your environment.
Ψ QMK home: /home/todd/qmk_firmware
Ψ Detected Linux (WSL).
☒ Can't find arm-none-eabi-gcc in your path.
☒ Can't find avr-gcc in your path.
☒ Can't find avrdude in your path.
☒ Can't find dfu-programmer in your path.
☒ Can't find dfu-util in your path.
Would you like to install dependencies? [Y/n] y
```

```
cd /path/to/qmk_firmware
make git-submodule
```

