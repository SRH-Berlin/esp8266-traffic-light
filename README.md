# Reproduction Steps
1. `git clone` [this respository](../..).
2. Open [sketch_apr9a.ino](./sketch_apr9a.ino).
3. Change `STASSID` and `STAPSK` to your WIFI credentials.
4. Wire the Red, Yellow and Green LEDs to pins `16`, `5`, and `4` (`16 : D0, 5: D1, 4 : D2`) respectively.
5. Upload the .ino file to your ESP8266
6. Open the Serial Monitor and wait for the ESP8266 to acquire an IP address.
7. Edit the [index.html](./index.html) file and replace [`<IP_ADDRESS>`](./index.html#L14) with the IP address from step 6.
8. Right click `index.html` in your file explorer and open it in your browser.
