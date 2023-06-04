# ESP32-ws2812-NTP-Clock
<p align="center">
        
[<img src="https://img.shields.io/github/v/tag/w4b-zero/ESP32_ws2812_NTP_clock?label=Relase&logo=data%3Aimage%2Fpng%3Bbase64%2CiVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAABhGlDQ1BJQ0MgcHJvZmlsZQAAKJF9kT1Iw1AUhU9TtVIqHewg4pChOlkQFXHUKhShQqgVWnUweekfNDEkKS6OgmvBwZ%2FFqoOLs64OroIg%2BAPi6uKk6CIl3pcUWsR44fE%2Bzrvn8N59gNCoMs3qGgM03TYzqaSYy6%2BIoVf0IIgoAgjLzDJmJSkN3%2Fq6pz6quwTP8u%2F7s%2FrUgsWAgEg8wwzTJl4nntq0Dc77xDFWllXic%2BJRky5I%2FMh1xeM3ziWXBZ4ZM7OZOeIYsVjqYKWDWdnUiCeJ46qmU76Q81jlvMVZq9ZY6578hZGCvrzEdVpDSGEBi5AgQkENFVRhI0G7ToqFDJ0nffyDrl8il0KuChg55rEBDbLrB%2F%2BD37O1ihPjXlIkCXS%2FOM7HMBDaBZp1x%2Fk%2BdpzmCRB8Bq70tn%2BjAUx%2Fkl5va%2FEjILoNXFy3NWUPuNwBBp4M2ZRdKUhLKBaB9zP6pjzQfwuEV725tc5x%2BgBkaVbpG%2BDgEBgpUfaaz7t7O%2Bf2b09rfj%2FJPHJjkWAKcAAAAAlwSFlzAAAN1wAADdcBQiibeAAAAAd0SU1FB%2BcGAw8EJudd3BAAAAEvSURBVEjHtZYxTsQwEEXfRIgNzbZcBIkjQE2FqFIimmVPAFeggRPQoaViQwsNBfSIkwAS2k%2FjIBMSx86akSJFk8k8%2Fz%2BOFfjnsOZG0hQ4Arb9fCsEvAE3ZvYVTZE0lfSq%2BLiTtBWtQNIxcAV8AM9upV2xCey69%2B6BAzN7j1Fw5lb2GFE7k7Ry9fWQkqLD47Bkswtg7mr3gdsQpGgPO8rX35C9EKQYsKOQVLmrGIAsJJVDM3ho5Stv51RjZjLKooGZLP7YJem8R0GvRUlKPIue1jkWOiCT5sGhS64kzTJC5k1yw33%2BuSC163XtJ0tJSw9ymk1BLkir%2BfJnBjkgHQMuQ8VJkNQDMAkyqnksJMmWVMhaK4%2BA1Nma90DkbcUy6q8iEjIBToAd4AW4NLPP0DvfUiJxtCJLzP0AAAAASUVORK5CYII%3D&style=plastic">](https://github.com/w4b-zero/ESP32_ws2812_NTP_clock/releases)
 &nbsp; 
[<img src="https://img.shields.io/github/last-commit/w4b-zero/ESP32_ws2812_NTP_clock?style=plastic&logo=data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAABhWlDQ1BJQ0MgcHJvZmlsZQAAKJF9kT1Iw0AcxV9TtSIVBTuIOASpgmBBVMRRq1CECqFWaNXB5NIvaNKQpLg4Cq4FBz8Wqw4uzro6uAqC4AeIq4uToouU+L+k0CLWg+N+vLv3uHsHCNUi06y2cUDTbTMRi4qp9KoYeEUH/OjFEEZlZhlzkhRHy/F1Dx9f7yI8q/W5P0e3mrEY4BOJZ5lh2sQbxNObtsF5nzjE8rJKfE48ZtIFiR+5rnj8xjnnssAzQ2YyMU8cIhZzTaw0McubGvEUcVjVdMoXUh6rnLc4a8Uyq9+TvzCY0VeWuU5zEDEsYgkSRCgoo4AibERo1UmxkKD9aAv/gOuXyKWQqwBGjgWUoEF2/eB/8LtbKzs54SUFo0D7i+N8DAOBXaBWcZzvY8epnQD+Z+BKb/hLVWDmk/RKQwsfAT3bwMV1Q1P2gMsdoP/JkE3Zlfw0hWwWeD+jb0oDfbdA15rXW30fpw9AkrqK3wAHh8BIjrLXW7y7s7m3f8/U+/sBa05ypE2o5wYAAAAJcEhZcwAADdcAAA3XAUIom3gAAAAHdElNRQfnBgMQJQCutahDAAABFklEQVRIx+2UO0pDQRSGv9GQ0qRKoZ2YCBZZQlYQXYBrcAHiCq5oG1egWNlIcBc210REEDfgA7VKiH5pBpQYL5cbbSQ/DMyc/5/zmMeBOf49Ql6hugQ04vI2hPD6KxmoDfVMHfqJYbTVZ3XeUl/UJzVR2+pmnD9HrlXUeU19VK/U5Sn8itpTH9RakQD78SjqGZr1qEmKBLhRz3Pouur1T/yCmvodI2AV6OfIpQesqaMpftISkADNiU1DYAeo5AhQAd6ADlCe4NKs0i/UO3UxQ1NS79VukTvYimXuZmj2oqZd9KmeqB/qgVr9Yq+qh5E7nuWjldUj9V0dqJdxDKKto5Zn7kVqE9gGNqKpD5yGENJ5O5/j7zEGJeQt/ASY9sUAAAAASUVORK5CYII=">](https://github.com/w4b-zero/ESP32_ws2812_NTP_clock/commit/main) &nbsp; 
[<img src="https://img.shields.io/github/watchers/w4b-zero/ESP32_ws2812_NTP_clock?style=plastic&logo=data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAABhWlDQ1BJQ0MgcHJvZmlsZQAAKJF9kT1Iw0AcxV9TtSIVBTuIOASpgmBBVMRRq1CECqFWaNXB5NIvaNKQpLg4Cq4FBz8Wqw4uzro6uAqC4AeIq4uToouU+L+k0CLWg+N+vLv3uHsHCNUi06y2cUDTbTMRi4qp9KoYeEUH/OjFEEZlZhlzkhRHy/F1Dx9f7yI8q/W5P0e3mrEY4BOJZ5lh2sQbxNObtsF5nzjE8rJKfE48ZtIFiR+5rnj8xjnnssAzQ2YyMU8cIhZzTaw0McubGvEUcVjVdMoXUh6rnLc4a8Uyq9+TvzCY0VeWuU5zEDEsYgkSRCgoo4AibERo1UmxkKD9aAv/gOuXyKWQqwBGjgWUoEF2/eB/8LtbKzs54SUFo0D7i+N8DAOBXaBWcZzvY8epnQD+Z+BKb/hLVWDmk/RKQwsfAT3bwMV1Q1P2gMsdoP/JkE3Zlfw0hWwWeD+jb0oDfbdA15rXW30fpw9AkrqK3wAHh8BIjrLXW7y7s7m3f8/U+/sBa05ypE2o5wYAAAAJcEhZcwAADdcAAA3XAUIom3gAAAAHdElNRQfnBgMQIw4fVyLCAAABc0lEQVRIx+3VsU7UQRAG8FlD6dGIjTZiUAk2WslrYIsIFkgH8hIiT6A+BQI2Gumw5gE0AQps1eqiZ/KjGSMc7P+OAzsm2WSz+823OzPfzkZcWg8rvQAoEfEwIu5ExI1c/hYRXyJip5RioJNxHavYV7f9xIychbhgGT/xG2uYxgRaOSbwBO/QwQ+8yGgbyVtJCBu428eF7mEzfdZwtQYcxue89eIAKV1M3220ujeHsIVfmKoQ3MbzHKMVzFQe8hFDRzdWM8SZiuMztI8Ut425CnY2Ma/+LkziD1433Lx9ioLaDZG8Sc7JyNTsncjbP/BCg0znG8Syh60r/dRvwL34nyl6m5yPuos8W3GYO6XITVhY6Zbpp5RYTaajmM9xq4J5nBwfjsn0gh7aUvWhVVrFJsb7IB7H+56toqvZLWUD62AdM7ifUQ7n/Gn2qw6+Z6soZwl5BCvYbXgHu3iJa+f9cB5ExFhE3Mzlg4j4WkrZufyzz22HLVGbc9t11cgAAAAASUVORK5CYII=">](https://github.com/w4b-zero/ESP32_ws2812_NTP_clock/watchers) &nbsp; 
[<img src="https://img.shields.io/github/license/w4b-zero/ESP32_ws2812_NTP_clock?style=plastic&logo=data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAABhWlDQ1BJQ0MgcHJvZmlsZQAAKJF9kT1Iw0AcxV9TtSIVBTuIOASpgmBBVMRRq1CECqFWaNXB5NIvaNKQpLg4Cq4FBz8Wqw4uzro6uAqC4AeIq4uToouU+L+k0CLWg+N+vLv3uHsHCNUi06y2cUDTbTMRi4qp9KoYeEUH/OjFEEZlZhlzkhRHy/F1Dx9f7yI8q/W5P0e3mrEY4BOJZ5lh2sQbxNObtsF5nzjE8rJKfE48ZtIFiR+5rnj8xjnnssAzQ2YyMU8cIhZzTaw0McubGvEUcVjVdMoXUh6rnLc4a8Uyq9+TvzCY0VeWuU5zEDEsYgkSRCgoo4AibERo1UmxkKD9aAv/gOuXyKWQqwBGjgWUoEF2/eB/8LtbKzs54SUFo0D7i+N8DAOBXaBWcZzvY8epnQD+Z+BKb/hLVWDmk/RKQwsfAT3bwMV1Q1P2gMsdoP/JkE3Zlfw0hWwWeD+jb0oDfbdA15rXW30fpw9AkrqK3wAHh8BIjrLXW7y7s7m3f8/U+/sBa05ypE2o5wYAAAAJcEhZcwAADdcAAA3XAUIom3gAAAAHdElNRQfnBgMQJg8VJ+YRAAAB2ElEQVRIx+WWsWsUURDGf++y4EG4CEmtoCAkjRaiCArxVKKdgoqlQlJopZ1E9DD+D1raaBGwUwsbiWitISoIEkIQRNNpEEzA82czJ8tm3bsL2OhUOzPfzPe9eW/3LfxXpt5Rb/dTk/XJMdavqKwH1SeAPeFuj9jV8BdSSk82O44RddbuNquOdGs2rq6XFK+p02oWuDl1Lp6zyK2V1K2r43mCYbWl3g3Ae/W6OloQ8psgFxtTb0SN0aOlDpet5FaAVtWtJfkNBBEfUr9G7Uw+V8uB6sBF4C3QACb72LIpYChqL0WvDSqmQsFh9Zm63Jl9lxENqEuRa0aPyTKCBfW1mtRTATzdA8GZwJ4Mf159o6Y86FiAzodfUxfV5z0QvIgVDIR/IXodzYMeqyv52alXArj/TwTq3sBczsW2qJ/UR53ALrWttgrKGuoX9V4Fwf2yE6feVH+qoxkwEafpoHoOWAYGgUNAGzhecXomgB/AtPoS+AbsAJpAAo6g1tUZ9XPhbWyrT9UDFSvYpz5UvxdqF9Vraj3ljxuwG9gGrALvUkorxU0GSCk1C/HBUN4APqaUPmz2A1j6JldZ7W9fUlmF2rPAzkK4eB90bCml9KDfcczbu736d38UfgH+YI1qJvNNrAAAAABJRU5ErkJggg==">](https://raw.githubusercontent.com/w4b-zero/ESP32_ws2812_NTP_clock/main/LICENSE) &nbsp; 
[![IMAGE_ALT](https://img.shields.io/github/languages/code-size/w4b-zero/ESP32_ws2812_NTP_clock?style=plastic&logo=data%3Aimage%2Fpng%3Bbase64%2CiVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAABhWlDQ1BJQ0MgcHJvZmlsZQAAKJF9kT1Iw0AcxV9TtSIVBTuIOASpgmBBVMRRq1CECqFWaNXB5NIvaNKQpLg4Cq4FBz8Wqw4uzro6uAqC4AeIq4uToouU%2BL%2Bk0CLWg%2BN%2BvLv3uHsHCNUi06y2cUDTbTMRi4qp9KoYeEUH%2FOjFEEZlZhlzkhRHy%2FF1Dx9f7yI8q%2FW5P0e3mrEY4BOJZ5lh2sQbxNObtsF5nzjE8rJKfE48ZtIFiR%2B5rnj8xjnnssAzQ2YyMU8cIhZzTaw0McubGvEUcVjVdMoXUh6rnLc4a8Uyq9%2BTvzCY0VeWuU5zEDEsYgkSRCgoo4AibERo1UmxkKD9aAv%2FgOuXyKWQqwBGjgWUoEF2%2FeB%2F8LtbKzs54SUFo0D7i%2BN8DAOBXaBWcZzvY8epnQD%2BZ%2BBKb%2FhLVWDmk%2FRKQwsfAT3bwMV1Q1P2gMsdoP%2FJkE3Zlfw0hWwWeD%2Bjb0oDfbdA15rXW30fpw9AkrqK3wAHh8BIjrLXW7y7s7m3f8%2FU%2B%2FsBa05ypE2o5wYAAAAJcEhZcwAADdcAAA3XAUIom3gAAAAHdElNRQfnBgMRBAFU7%2BcBAAABg0lEQVRIx72WsUtbURTGf%2FdhKOpmN5eSwdVOMYUWCkKhVOPgIM1f4JjRNWMnO5R2Lx1FJylth1QdBEFQ3MShVB0FkUihWvx1uYXweGmSl5g7nvu9%2B53vnPMdHgzzqHPqud2fn2rlf2%2BGFMEZcAl87pDLM%2BApsA88BqohhPVuFKjWu8DVI3ZMbah%2F1GoWNumnpCGEX8A8sAN8yiJJ%2Bu1bJFkAdoGP6Z7kJfgdS%2FUwklwDr4BD4N0gCL4At8DFv3ECmkAJeNQKHMlZlgN1BqgA4xnT1XY6jtTXffioHtVkKwghTA%2FavMl9b4ekRd6EuqWupmS%2FVb%2BrE7kJ1MloljLwLYX5CjwBtiOu58YU1RO1qb5og3muXqk%2F1Klemox6rN6opQ6JlCLuuBeCBFgDCkBNLbT5sADUIm4tT5lW1Dt1Ux1N3T1QN6Jh3%2FTqg9bL5bh236fiH2J8OY%2FR0oBZtZyKldXZQTm5kbF39vox2khGFktAMed7i8BZJ5lH5j%2Bn6suh%2Fqn8BbHck7yUqD2nAAAAAElFTkSuQmCC)](https://github.com/w4b-zero/ESP32_ws2812_NTP_clock/archive/refs/heads/main.zip) <br> 
[![Discord](https://img.shields.io/discord/1106048601269993482?logo=discord&logoColor=ffffff&style=plastic&color=5865F2)](https://discord.gg/kteShSHU) &nbsp; 
[![IMAGE_ALT](https://img.shields.io/static/v1?label=Editor&message=Visual%20Studio%20Code&style=plastic&logo=visualstudiocode&color=007ACC)](https://code.visualstudio.com/) &nbsp; 
[![IMAGE_ALT](https://img.shields.io/static/v1?label=IDE&message=Platformio&style=plastic&color=ff7f00&logo=data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAABhWlDQ1BJQ0MgcHJvZmlsZQAAKJF9kT1Iw0AcxV9TtSIVBTuIOASpgmBBVMRRq1CECqFWaNXB5NIvaNKQpLg4Cq4FBz8Wqw4uzro6uAqC4AeIq4uToouU+L+k0CLWg+N+vLv3uHsHCNUi06y2cUDTbTMRi4qp9KoYeEUH/OjFEEZlZhlzkhRHy/F1Dx9f7yI8q/W5P0e3mrEY4BOJZ5lh2sQbxNObtsF5nzjE8rJKfE48ZtIFiR+5rnj8xjnnssAzQ2YyMU8cIhZzTaw0McubGvEUcVjVdMoXUh6rnLc4a8Uyq9+TvzCY0VeWuU5zEDEsYgkSRCgoo4AibERo1UmxkKD9aAv/gOuXyKWQqwBGjgWUoEF2/eB/8LtbKzs54SUFo0D7i+N8DAOBXaBWcZzvY8epnQD+Z+BKb/hLVWDmk/RKQwsfAT3bwMV1Q1P2gMsdoP/JkE3Zlfw0hWwWeD+jb0oDfbdA15rXW30fpw9AkrqK3wAHh8BIjrLXW7y7s7m3f8/U+/sBa05ypE2o5wYAAAAJcEhZcwAADdcAAA3XAUIom3gAAAAHdElNRQfnBgQCJyAlmKWuAAACHUlEQVRIx6WUvWtUQRTFz6yLa1SUjYmgIgsqiBAIJmCTJnaSwiIKWlhF8Q8Q7EULLRQbgxYSQooEDfhBtDWWBhIMaGFINIg2KkSz4geyOz+bK05e5uXt25xmePfcOffOvDtHigA4DEwCN2q1mlMKgBZgCHgCVNQogFH+o2uNvONB3mCeAqeAX8AbYHNanve+HfgIVIGjygNgLzDVQN4ccCCNL6YRzrkPQBlol7Qsab+kVkkFSV8lLQJtkjY45xaUF0AHMA3MA3VWwwOfgJdATx7hik1FXjwDDmWJ9wLfaB4/gd4VVx2I75M0KwlJ45Kqkk5L2pVx6Kqkx5K+SDohaYekTufcu2T394ElK/Qvtgm4s0bHk977cpC/BZgCxpLz3AL8Bi6lXN14RPwtsDWSewz44b3fmLQGgIGUB1WJFDiT0kzZ+A7ZTEvSNlv3WFIRuAaMAeVCofBe0otA54+kh4EXDdubkKRuW0thhwet6jxQAo4AM+GpgNtB968s1m3fM8A5iz2wWCV5tM9GXK/X6yUzvAlgt/GDQYHpiJu2AX3GL8bu7mogcD7CDwX8XITvAb4bfzn2I1uB5UDkClC0zQ5YWOET3u8MxE8G4kve++1pL3kgMSmvLXYxMkWjQD/wNBHvz7KLu+uwipuNmF0RuNeE+EgeRy0CIznEb6kZABeAWoZ7ntV6AHQCsxHx55n+n6OIs4mZAB4BfY3u/QtzxxP/cH8MxQAAAABJRU5ErkJggg==)](https://platformio.org/)
</p>

Internet Time Clock (Ring 60Leds + Clock 58Leds) for PlatformIO<br>
<img src="/images/ESP32_WS2812b_Uhr.jpg" width="400px"><br>
On first launch, an unsecured Wifi Access Point will be created!<br>
When connecting to this you will be redirected to your browser to the web configuration panel. (192.168.4.1)<br>
Please select your router there and enter your password.<br>
Selectable languages are German, English and Dutch.<br>
With the help of a checkbox you can protect the web control panel with a password, which you can enter in the text field below.<br>
*The password already contained therein was automatically generated at the first start.*<br>
Finally, all you have to do is click on save - if everything went well, `##**##**##**` should appear in the wifi password text field.<br>
Now you can click Reboot device to connect to your router.<br>
<br>
To call up the web configuration panel again, you have to press the "Start Config Button" for about 3 seconds when restarting/switching on. <br>
<br>

## Used Libraries

<ul>
	<li> adafruit/Adafuit NeoPixel@^1.10.6 </li>
	<li> https://github.com/taranais/NTPClient </li>
	<li> https://github.com/Arduino-IRremote/Arduino-IRremote </li>
	<li> paulstoffregen/OneWire @ ^2.3.7 </li>
	<li> milesburton/DallasTemperature @ ^3.11.0 </li>
	<li> https://github.com/Juerd/ESP-WiFiSettings </li>
</ul>
<br>

## Custom ESP Board<br>

<img src="/images/board.jpg" width="400px"><br>
<br>

## Used Pins<br>

Start Config Button   = GPIO 27<br>
LEDs WS2812b          = GPIO 16<br>
Button                = GPIO 17 (Nightmode / Daymode)<br>
IR TSOP38238          = GPIO 21<br>
Relay SRD-05VDC-SL-A  = GPIO 22<br>
Temp DS18B20          = GPIO 18<br>
<br>


## arrangement of LEDs<br>

<img src="/images/LED_order.jpg" width="400px"><br>
<br>


## ESP32 mini<br>

<img src="/images/ESP32_d1_mini.jpg" width="200px"><br>
<br>


## IR Remote<br>

<img src="/images/IR_Remote.jpg" width="200px"><br>
ON / OFF All Led Off used Relay<br>
1 = Date<br>
2 = Year<br>
3 = Temp<br>
4 = Test Numbers<br>
5 = Rainbow <br>
6 = Rainbow<br>
7 = Rainbow<br>
8 = Nightmode / Daymode<br>


## My Discord Server

<a href="https://discord.gg/kteShSHU"><img src="https://discord.com/api/guilds/1106048601269993482/widget.png?style=banner2" width="25%"></a> <br>
