<!-- PROJECT SHIELDS -->
[![Facebook][facebook-shield]][facebook-url] [![LinkedIn][linkedin-shield]][linkedin-url]  [![Twitter][twitter-shield]][twitter-url]  

[![License][license-shield]][license-url] <!--[![Build Status][build-shield]]() [![Contributors][contributors-shield]]()--> 



<!-- PROJECT LOGO -->

<br />
<p align="center">
  <a href="https://e-nable.fr/">
    <img src="https://e-nable.fr/wp-content/uploads/2015/12/e-nable-france.png" alt="Logo" width="160" height="179">
  </a>

  <h3 align="center">Hackberry Hand project</h3>

   <p align="center">
    <br />
    <a href="https://github.com/Thomas-Broussard/hackberry-enableFrance/wiki"><strong>Explore the docs »</strong></a>
    <br />
    <a href="https://github.com/Thomas-Broussard/hackberry-enableFrance/releases/latest"><strong>Get the latest release »</strong></a>
    <br />
    <br />
    <a href="https://www.youtube.com/watch?v=6Jfwinhh8ZM">View Demo</a>
    ·
    <a href="https://github.com/Thomas-Broussard/hackberry-enableFrance/issues">Report Bug</a>
    ·
    <a href="https://github.com/Thomas-Broussard/hackberry-enableFrance/issues/new">Request Feature</a>
  </p>
</p>



<!-- TABLE OF CONTENTS -->
## Table of Contents

* [About e-Nable France](#about-e-nable-france)
* [About the Project](#about-the-project)
  * [Built With](#built-with)
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
  * [Installation](#installation)
* [Usage](#usage)
* [Contributing](#contributing)
* [Additional Resources](#additional-resources)
* [PCB](#pcb)
* [License](#license)
* [Contact](#contact)
* [Acknowledgements](#acknowledgements)


## About e-Nable France

![eNableFrance Logo](https://e-nable.fr/wp-content/uploads/2015/12/IMG_5615-e1479374257379-1024x672.jpg)

Every year, in France, more than three hundred children are born with agenesis (a member who has not completely formed before birth).

We use 3D printing technologies to design, manufacture and offer assistive devices to people without fingers.

Children grow up and their devices need to be renewed every 12 to 18 months.

Thanks to your donations and their generosity, our network of makers equips people free of charge by making the request.

The primary mission of e-Nable France is to bring together and connect people who need a device with people who can make it.

<!-- ABOUT THE PROJECT -->
## About The Project

[![Hackberry Hand][product-screenshot]](http://exiii-hackberry.com/)


Hand hackberry is a myolectric prosthesis (Prosthesis controlled by muscle sensors placed on the arm to control it) for people with disabilities hand to regain autonomy in everyday life: social, professional, transport, ...

These prototypes are still limited for everyday use in comparison to the models on the market, but they have the following characteristics:

* The total cost of the prosthesis is less than 1000€ (10 000 to 70 000 € on the market)
* The main parts (fingers, palm, socket) are made with a 3D printer
* Parts plans, material list and manufacturing tutorials are [online](https://github.com/mission-arm/HACKberry) so that the prosthesis can be made and contribute to the development of the prosthesis by sharing these results (open source)

Its goal is to federate a team around the construction of a lower limb prosthesis at low cost with standardized and open source parts. They are easily repairable and therefore accessible to people with limited financial resources. He wants to help emerging countries that do not have access to prosthetic equipment.


### Built With

* 3D printers for plastic parts
* IDE for microcontrollers programming : 
  * [Visual Studio Code](https://code.visualstudio.com/)
  * [PlatformIO](https://platformio.org/)
* Mobile app IDE (optional) : 
  * [Android Studio](https://developer.android.com/studio)


<!-- GETTING STARTED -->
## Getting Started

An overview of tools required to flash devices, usage of basic examples and more.

### Prerequisites

To build files and flash them on microcontrollers, you'll need to download [Visual Studio Code](https://code.visualstudio.com/) 

Once installed, you need to download [PlatformIO](https://platformio.org/) extension : 

1. Open Visual Studio Code
2. Click on the "Extension button" (Ctrl + Shift + X)
3. In the Extensions:MartketPlace, search for « PlatformIO ».The PlatformIO IDE will appears. 
4. Click on "Install".
5. When installation is finished, click on "reload" or close/reopen Visual Studio Code.

### Installation

Clone the repository
```sh
git clone https://github.com/Thomas-Broussard/hackberry-enableFrance.git
```


<!-- USAGE EXAMPLES -->
## Usage

1. On Visual Studio code, click on <i>File > Open Folder...  (Ctrl+K Ctrl+O)</i>

2. Select folder <i><b>hackberry-enableFrance/example/basics_debug/</b></i>

3. Click on Build to compile the code

4. Plug your device (Hackberry Hand or Arduino Nano)

5. Click on Upload to load program on the device

![Product Name Screen Shot](https://docs.platformio.org/en/latest/_images/platformio-ide-vscode-build-project.png)



_For more details, please refer to the [PlatformIO Documentation](https://docs.platformio.org/en/latest/ide/vscode.html)_



<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project  
<img src="https://help.github.com/assets/images/help/repository/fork_button.jpg" alt="Fork" width="449" height="70">

2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request


<!-- ADDITIONAL RESOURCES -->
## Additional Resources

* [Facebook : eNable Robotics France](https://www.facebook.com/groups/eNable.robotics.France/)
* [Details on eNable France robotics Projects](https://e-nable.fr/projet-robotique/)
* [3D Printing Files for Hackberry Hand](https://github.com/mission-arm/HACKberry/tree/master/HACKberry_3Dmodel/STL)
* [Instruction files for Hackberry Hand (FR)](https://drive.google.com/drive/folders/1PkoY7QRCFFofEhJ_Oy8mezCnoT-idXC4)


<!-- PCB -->
## PCB

* [Original Mk2 Handboard](https://easyeda.com/thomas.broussard91/hackberry)
* [Mk3 : Evolution of the Mk2 Handboard](https://easyeda.com/thomas.broussard91/exphackberry)
* [Extension board for Mk3 Handboard](https://easyeda.com/thomas.broussard91/extension_hackberry)


<!-- LICENSE -->
## License

This policy (“Policy”) of “HACKberry Open Source Project” ( “Project”) sets forth the scope and the terms and conditions of the provision of the source codes and data etc. regarding “HACKberry” by Exiii Inc. (“Company”).

See [Hackberry Original Project License](https://github.com/mission-arm/HACKberry) for more information.

<!-- CONTACT -->
## Contact

* Thomas Broussard - thomas@e-nable.fr

* e-Nable France - [@enableFrance](https://twitter.com/enableFrance) - contact@e-nable.fr

* Hackberry Project : [http://exiii-hackberry.com/](http://exiii-hackberry.com/)



<!-- ACKNOWLEDGEMENTS -->
## Acknowledgements

### Main contributors
* [e-Nable France](https://e-nable.fr/)
* [Genta Kondo (Author of Hackberry Project)](https://github.com/mission-arm/HACKberry)
* [Exiii](https://exiii.jp/)

### Open Source License Acknowledgements
* [Best README Template by othneildrew](https://github.com/othneildrew/Best-README-Template)
* [XLoader by Geir Lunde](http://xloader.russemotto.com/)


<!-- MARKDOWN LINKS & IMAGES -->
[build-shield]: https://img.shields.io/badge/build-passing-brightgreen.svg?style=flat-square
[contributors-shield]: https://img.shields.io/badge/contributors-1-orange.svg?style=flat-square

[license-shield]: https://img.shields.io/badge/license-GPLv3-blue.svg?style=flat-square
[license-url]: http://www.gnu.org/licenses/quick-guide-gplv3.en.html

[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=flat-square&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/company/e-nable-france/

[facebook-shield]: https://img.shields.io/badge/-Facebook-black.svg?style=flat-square&logo=facebook&colorB=555
[facebook-url]: https://www.facebook.com/enableFrance/

[twitter-shield]: https://camo.githubusercontent.com/83d4084f7b71558e33b08844da5c773a8657e271/68747470733a2f2f696d672e736869656c64732e696f2f747769747465722f75726c2f687474702f736869656c64732e696f2e7376673f7374796c653d736f6369616c
[twitter-url]: https://twitter.com/enablefrance

[product-screenshot]: http://exiii-hackberry.com/wp-content/themes/bones/library/images/hackberry_images/HBrenderRGB.jpg
