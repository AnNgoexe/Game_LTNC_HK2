# Game_LTNC_HK2

## GAME INTRODUCTION
+ Name: Ngo Quoc An  <br/>
+ Student ID number: 22026515 <br/>
+ This is my game project based on Google running dinasour with added other interesting game features and fuctions. <br/>
+ Using SDL2.0 library , C/C++ <br/>

## HOW TO PLAY GAME
Please read the instruction carefully to understand the game law and avoid UNNECESSARY misunderstanding <br/>
Your task is to reach the highest score by receiving awards while the game character is still alive. <br/>
1. When game menu appears, click "Play" button to start or "Instruction" button to read instruction. If you do not want to play, click "Exit" button to exit.
2. While playing, press button "Space" to avoid danger (bat,stone and cactus) and receive awards (diamond,coin and heart). Besides, click "Pause" button to stop playing for a while and click "Resume" button to continue.
3. There are 3 numbers on the screen: score, life and road <br/>
+ At first, game character has 3 lives. Every time it collides with a danger, its life will decrease by 1. If the number of lives is smaller than 1, you lose. <br/>
_ BAT and CACTUS threats appear continuously. BAT appears in the air and CACTUS appears on the ground. <br/>
_ Please watch out the STONE threat. It only appears after an amount of time from the sky and falls toward the character. PLEASE BE CAREFUL !!!
+ Score will increase depending on the award. If a coin, score will increase by 10. If a diamond, score will increase by 20. If a heart and the number of lives is smaller or equal to 3, life will increase by 1. <br/>
_ DIAMOND and COIN award appear continuously in the air. <br/>
_ HEART award only appears after an amount of time. <br/>
+ Road number increases continuously and shows the number of metres that game character has run. <br/>
4. If you lose the game, a picture will appear to show your effort depending on the number of stars <br/>
+ If your score is greater than or equal to 500, you will receive 5 stars  <br/>
+ If your score is greater than or equal to 300, you will receive 4 stars  <br/>
+ If your score is greater than or equal to 100, you will receive 3 stars  <br/>
+ If your score is greater than or equal to 50, you will receive 2 stars   <br/>
+ If your score is greater than or equal to 0, you will receive 1 star     <br/>
5. There are two choices at the end of the game <br/>
+ Press "Esc" button on the keyboar to exit the game. <br/>
+ Press "Space" button on the keyboard to play again. <br/>
## MAIN FUCTIONS
+ LTexture - handling with loading media <br/>
+ Game character - movement and animation of the game character <br/>
+ Game threats - movement and animation of the game threats <br/>
+ Game awards - movement and animation of the game awards <br/>
+ Game buttons - loading button image and handling with Play, Help, Exit, Pause, Continue button <br/>
+ Logic game - handle with collision , update score, ... <br/>
## MEDIA SOURCE
+ Image: Using image mainly from https://fr.pngtree.com/ and https://www.pngwing.com/ then edit. <br/>
+ Music and sound: Using https://www.y2mate.com/fr498 to convert Youtube video to mp3 file, then use https://convertio.co/vn/mp3-wav/ to convert mp3 to wav <br/>
## REFERENCE
+ Instruction: https://lazyfoo.net/ <br/>
+ Idea: https://github.com/manhhung2111/Dino-run <br/>
+ Inspiration: https://www.youtube.com/watch?v=5bblnJx5GWk <br/>
