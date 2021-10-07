# phone_to_opengl
Connect your phone's rotation sensing to OpenGL using Node JS and ASIO

## How to Build
`./build`

## How to Run
1. Run `sudo ./visual_server.out`
2. On another terminal run `sudo node server.js`
3. On your phone go to https://$YOUR_INTERNAL_IP_ADDRESS/ on your web browser. You can get your ip address on Linux by using the "hostname -I" command. It most likely is "192.168.XXX.XXX". The "https://" in the address is mandatory. 
4. Click "Calibrate" on your phone with the phone flat, facing up, and vertical.
5. Rotate your phone. You should see the rectangular prism on the screen rotate too! 
