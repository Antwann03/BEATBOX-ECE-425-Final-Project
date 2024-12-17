<h1>Introduction</h1>

<hr><p>The Keil uVision5 project files for my BEATBOX project, created for the Fall 2024 ECE 425 (Microprocessor Systems) course, are available in this repository. The project makes use of the TM4C123GXL LaunchPad, including a rotary encoder, 16x2 LCD, and a magnetic buzzer to create an interactive system in which users may pick and play different tunes. 
  
<p>Performed By:</p>
<ul>
  <li>Antonio Anzora Jr</li>
</ul>

<p>Professor:</p>
<ul>
  <li>Aaron Nanas</li>
</ul>
</p>
<h1>Description</h1>

<hr><ul>
<li>The project utilizes the TM4C123GXL LaunchPad Microcontroller to create an interactive music player system capable of playing 4 different songs. The setup includes a magnetic buzzer for audio input, a 16x2 LCD Display for menu navigation and song selection, a rotary encoder for user input, and jumper wires for connectivity. This combination allows users to select and play songs with visual feedback through display.</li>
</ul>

<h1>Project Goals</h1>

- **Gain experience in designing a system that integrates hardware and software to create a functional music-playing device.**
    - **Purpose**: This project will involve designing the hardware components (e.g., magnetic buzzer, LCD, rotary encoder) and developing the software to interface with them, allowing for a seamless user experience.

- **Design and implement a user-friendly interface with a rotary encoder and LCD for song selection.**
    - **Purpose**: The goal is to create an easy-to-use interface that allows users to interact with the system by selecting songs through the rotary encoder while providing visual feedback on the LCD.

- **Design and implement custom character display on the LCD using CGRAM.**
    - **Purpose**: This goal focuses on developing custom pixel art representations (e.g., Mario) for display on the 16x2 LCD. The custom characters will be stored in CGRAM and displayed based on user input or song selection.

- **Learn to handle limited memory resources effectively for custom character and sound data.**
    - **Purpose**: The project will provide experience in managing memory limitations, especially in terms of storing custom characters on the LCD and handling sound data for the magnetic buzzer. This includes learning how to maximize the system's memory efficiency.

<h1>Video Demonstration</h1>
<ul>
<li>Super Mario Theme Song and Doom Theme Song: <a href="https://drive.google.com/drive/folders/1fADChxdK__N7KiT_LdD1QoKrhce_fi9T?usp=drive_link">Link</a></li>
<li>Tyler, The Creator - Like Him: <a href="https://drive.google.com/drive/folders/1rKp0JsDf6UEdUzbWrCa92Q6y5mm0yF5g?usp=drive_link">Link</a></li>
  <li>Rapp Snitch Knishes - MF DOOM, Mr. Fantastik: Coming soon</li>
</ul>


<h1>Block Diagram</h1>
<hr>
<ul>
  
![BeatBox_BlockDiagram](BeatBox_BlockDiagram.png)
</ul>
<h1>Components Used</h1>
<hr><p>


|         Description                   | Quantity          |    Manufacturer   |    Price ($)       |    Link       |
|         :-------------:                 |:-------------:    | :-----:            |    :-----:          |    :-----:          |
| Tiva C Series TM4C123G LaunchPad      | 1                 | Texas Instruments |   22.99 per unit   |    [Product Link](https://www.mouser.com/ProductDetail/Texas-Instruments/EK-TM4C123GXL?qs=TB%2FQ0sBK%2FGefKGr%252BQsiJWQ%3D%3D)       |
| USB-A to Micro-USB Cable              | 1                 |       N/A         |   2.48 per unit    |    [Product Link](https://www.digikey.com/en/products/detail/sparkfun-electronics/CAB-24508/22321088?gclsrc=aw.ds&&utm_adgroup=&utm_source=google&utm_medium=cpc&utm_campaign=PMax%20Shopping_Product_Low%20ROAS%20Categories&utm_term=&utm_content=&utm_id=go_cmp-20243063506_adg-_ad-__dev-c_ext-_prd-22321088_sig-CjwKCAiAmfq6BhAsEiwAX1jsZ-H07hC3CwGiLi2op_HnKewSouCI1NDJatIYMBnhYX5nmB_97Dw_4xoCQnAQAvD_BwE&gad_source=1&gclid=CjwKCAiAmfq6BhAsEiwAX1jsZ-H07hC3CwGiLi2op_HnKewSouCI1NDJatIYMBnhYX5nmB_97Dw_4xoCQnAQAvD_BwE&gclsrc=aw.ds)      |
|         EduBase Board                 | 1                 |   Trainer4Edu     |   148.00 per unit  |    [Product Link](https://www.trainer4edu.com/edubase_v2/ti_arm_tiva_msp432_launchpad.html)       |
|     Small Flathead Screwdriver        | 1                 |       N/A         |   1.19 per unit    |    [Product Link](https://www.sykessler.com/product/small-flat-head-screwdriver/)       |
|     PMOD ENC (Rotary Encoder)         | 1                 |       N/A         |   6.99 per unit    |    [Product Link](https://digilent.com/shop/pmod-enc-rotary-encoder/?srsltid=AfmBOoogCrdWyBcuDFI5qA5gxddaanvtuNNJUkPz-lh6bLyRYOKz-AXH)       |

</p>

<h1>Songs Available</h1>
<hr><p>

| Song Name                  | Duration       | Genre          | Menu Option | Special Notes                            |
|:--------------------------:|:--------------:|:--------------:|:-----------:|:----------------------------------------:|
| Super Mario Bros Theme     | Approx. 1 min  | Video Game     | Option 1    | Nostalgic and iconic                     |
| Doom Theme Song            | Approx. 1 min  | Game/Metal     | Option 2    | Intense and thrilling                    |
| Like Him - Tyler the Creator | Approx. 1 min| Hip-Hop        | Option 3    | Reflective and deep                      |
| **TBD:** MF Doom (MM..Food)| Approx. 1 min  | Hip-Hop        | Option 4    | A tribute to MF Doom's creative genius   |
</p>
</ul>

<h1>Drawing Mario on a 16x2 LCD: A Step-by-Step Tutorial</h1>
General Procedure:

1. We begin by designing a 5x8 pixel representation of Mario that fits into the custom character slots of the 16x2 LCD.
2. Use a pixel art tool or online link (like a pixel editor) to create the design. You can use this link to get an idea of how the Mario pixel design should look on the 16x2 LCD. [Click Here](https://chareditor.com/)
3. The design will take up 6 parts of 5x8 pixel art for Mario's torso, legs, head, etc.
4. Next, using another online tool or design editor, create separate shapes for Mario's torso, leg, head, etc., ensuring that you use blue as the background color and select the Hex data type for each shape.[Click Here]( https://maxpromer.github.io/LCD-Character-Creator/)
5. For each shape, obtain the Hexadecimal values for each 5x8 character representation.
6. These Hexadecimal values should be 8 characters long (e.g., `0xFF, 0x81, 0x81, ...`), and you can copy and paste them directly.
7. After obtaining the Hexadecimal values for Mario’s design, place these values into the header file that controls the LCD.
8. This involves declaring these values as custom characters for the 16x2 LCD to reference them in your main code for display.
9. Finally, you can call the custom character functions in your main program to display the Mario logo on the 16x2 LCD screen. Ensure that you position the custom characters properly across the two lines of the LCD.
10. With these steps, Mario should be displayed across the 16x2 LCD as a series of custom characters, giving you a pixelated Mario design! The key is ensuring that each part of the design is carefully mapped and represented using the 5x8 matrix custom characters.
11. It’s important to note that the 16x2 LCD has a limitation when it comes to displaying custom characters. The LCD's Character Generator RAM (CGRAM) can only store up to 8 custom characters at a time. Each custom character takes up 1 byte of memory, and since there are only 8 available slots, this limits the number of designs you can display at any given time. If you need to display more custom characters, you'll have to overwrite existing ones, which may require careful management of character memory to ensure the desired display.

<h1>Acknowledgement</h1>
<hr><ul>
<li>Ever since I was young, I have always enjoyed playing Super Mario Bros, which sparked my interest in learning how to display characters on an LCD. My initial plan was to familiarize myself with basic LCD techniques and eventually move on to a more ambitious project—a Super Mario Bros game using a different type of LCD display. This is why I decided to include a mini animation for Mario with his theme song playing in the background. Another key motivation for choosing this project was the recent release of a new album by one of my favorite artists. This inspired me to explore the possibility of playing music through a magnetic buzzer, combining my love for music with my interest in electronics and programming.</li>
</ul><ul>
<li>This project was built upon various tutorials and guides that provided essential knowledge on programming the TM4C123GXL LaunchPad and interfacing with components such as the LCD, rotary encoder, and magnetic buzzer. These resources helped me understand the necessary coding techniques and hardware connections required to develop the system.</li>
</ul><ul>
<li>I greatly appreciate the clear explanations and step-by-step instructions that made it possible to integrate these components seamlessly. Special thanks to Professor Aaron Nanas and the ECE 425 Microprocessor Systems course for their comprehensive insights and support throughout the development process.</li>
</ul>

<h1>Contact</h1>
<hr><p><span style="margin-right: 30px;"></span><a href="https://www.linkedin.com/in/antonio-anzora-jr-877380239/"><img target="_blank" src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/linkedin/linkedin-original.svg" style="width: 10%;"></a><span style="margin-right: 30px;"></span><a href="https://github.com/Antwann03"><img target="_blank" src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/github/github-original.svg" style="width: 10%;"></a></p>
