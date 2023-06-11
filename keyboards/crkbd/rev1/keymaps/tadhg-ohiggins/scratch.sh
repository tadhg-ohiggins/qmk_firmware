# Following https://docs.qmk.fm/#/newbs_getting_started

qmk setup --help
qmk setup 

# Lots of brew problems here, I ended up upgrading to Monterey, which didn't actually solve them but got some things out of the way.

brew search avr-gcc
brew info osx-cross/avr/avr-gcc@8
echo 'export PATH="/usr/local/opt/avr-gcc@8/bin:$PATH"' >> ~/.zshrc

brew search arm-none-eabi-gcc
brew info osx-cross/arm/arm-none-eabi-gcc@8
echo 'export PATH="/usr/local/opt/arm-none-eabi-gcc@8/bin:$PATH"' >> ~/.zshrc

# Setup stuff mostly better at this point
qmk setup 

qmk compile -kb crkbd -km default
# Success!

brew install qmk-toolbox

qmk new-keymap -kb crkbd
# /Users/tadhg/vcs/qmk_firmware/keyboards/crkbd/rev1/keymaps/tadhg-ohiggins
cd keyboards/crkbd/rev1/keymaps/tadhg-ohiggins/


