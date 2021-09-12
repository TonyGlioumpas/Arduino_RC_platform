# Arduino_RC_platform

The platform chassis we used :  https://www.ebay.com/itm/201697381020?hash=item2ef619ca9c:g:QysAAOSwvedgUb3Y 
The gripper we used :  https://www.ebay.com/itm/264292005224?hash=item3d8907f568:g:sk4AAOSwf5FcuYjk

For the voltage regulation of the servomotors used to control the gripper and the camera movement we used a LM317 DC-DC step down converter https://www.ebay.com/itm/403151132011?hash=item5dddae156b:g:Mt0AAOSwIAJb~-Xp

The platform is remotely controlled using the "Arduino Bluetooth RC Car App" https://play.google.com/store/apps/details?id=braulio.calle.bluetoothRCcontroller&hl=en&gl=US
In order to identify the bluetooth signals sent by the application, we used a python script that can be run at any PC with a bluetooth module in it.
To make the plaform able to receive these signals, we used a HC05 JY-MCU anti-reverse, integrated Bluetooth serial pass-through module https://www.ebay.com/itm/264292005224?hash=item3d8907f568:g:sk4AAOSwf5FcuYjk

To control the two DC motors of the platform we used a HC05 JY-MCU anti-reverse, integrated Bluetooth serial pass-through module https://www.ebay.com/itm/191674305541?hash=item2ca0adcc05:g:Jb0AAOSwESNZ7v2s
