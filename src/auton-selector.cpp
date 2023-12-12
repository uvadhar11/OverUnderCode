#include "vex.h"
#include "linking.h"
#include "init.h"
using namespace vex;

// get default buttons (red + blue) and no auton selected showing up on the screen
void initalizeAutonSelector()
{
    Brain.Screen.setFillColor(red);
    Brain.Screen.drawRectangle(auton1Rect.xCoordinate, auton1Rect.yCoordinate, auton1Rect.rectWidth, auton1Rect.rectLength); // screen is 480 by 240. Paramters: x coord, y coord, width, height
    Brain.Screen.setCursor(5, 7);                                                                                            // row (up/down for vex brains), column (left/right) -> different numbers on row/cols -> to see, click on question mark near setCursor in the command sidebar under Looks
    Brain.Screen.print("AUTON 1");

    Brain.Screen.setFillColor(red);
    Brain.Screen.drawRectangle(auton2Rect.xCoordinate, auton2Rect.yCoordinate, auton2Rect.rectWidth, auton2Rect.rectLength); // x coord, y coord, width, height
    Brain.Screen.setCursor(5, 34);
    Brain.Screen.print("AUTON 2");

    Brain.Screen.setFillColor(blue);
    Brain.Screen.drawRectangle(auton3Rect.xCoordinate, auton3Rect.yCoordinate, auton3Rect.rectWidth, auton3Rect.rectLength);
    Brain.Screen.setCursor(9, 7);
    Brain.Screen.print("AUTON 3");

    Brain.Screen.setFillColor(blue);
    Brain.Screen.drawRectangle(auton4Rect.xCoordinate, auton4Rect.yCoordinate, auton4Rect.rectWidth, auton4Rect.rectLength);
    Brain.Screen.setCursor(9, 34);
    Brain.Screen.print("AUTON 4");

    Brain.Screen.setFillColor(transparent);

    // only print no auton selected if the current auton program selected is 0 (autonSelected == 0)
    if (autonSelected == 0)
    {
        Brain.Screen.setCursor(11, 3);
        Brain.Screen.print("AUTON SELECTED: NONE");
    }
}

// Function for Alliance Color Selection
void initalizeAllianceColorSelector()
{
    Brain.Screen.setFillColor(transparent);
    Brain.Screen.setCursor(2, 3);
    Brain.Screen.print("ALLIANCE COLOR: ");

    // draw red alliance color button
    Brain.Screen.setFillColor(red);
    Brain.Screen.drawRectangle(redButton.xCoordinate, redButton.yCoordinate, redButton.rectWidth, redButton.rectLength); // screen is 480 by 240. Paramters: x coord, y coord, width, height
    Brain.Screen.setCursor(2, 23);                                                                                       // row (up/down for vex brains), column (left/right) -> different numbers on row/cols -> to see, click on question mark near setCursor in the command sidebar under Looks
    Brain.Screen.print("RED");

    // draw blue alliance color button
    Brain.Screen.setFillColor(blue);
    Brain.Screen.drawRectangle(blueButton.xCoordinate, blueButton.yCoordinate, blueButton.rectWidth, blueButton.rectLength); // screen is 480 by 240. Paramters: x coord, y coord, width, height
    Brain.Screen.setCursor(2, 33);                                                                                           // row (up/down for vex brains), column (left/right) -> different numbers on row/cols -> to see, click on question mark near setCursor in the command sidebar under Looks
    Brain.Screen.print("BLUE");

    // print that no alliance color is selected + set fill to transparent ONLY if no auton is selected
    // otherwise it will flash between the selected one and none because this function is called to reset
    // the other rectangle's color to red/blue to eliminate the chance of having multiple green rectangles
    if (!(allianceColor == "RED" || allianceColor == "BLUE"))
    { // if allianceColor isnt red/blue...
        Brain.Screen.setFillColor(transparent);
        Brain.Screen.setCursor(11, 28);
        Brain.Screen.print("COLOR: NONE");
    }
    // return 0;
};

// Auton Screen Selector Function
void autonScreenSelector()
{
    if (Brain.Screen.pressing())
    { // if the screen is touched. x and y position() allows to get the x and y of the touch on the screen

        // if statements for which auton is selected based on which rectangle is pressed (where press is)
        // use x coordinate for drawing rectangle and NOT for pressing since 2 coordinates are 0!!!
        if (Brain.Screen.xPosition() < 240 && (Brain.Screen.yPosition() > auton1Rect.yCoordinate && Brain.Screen.yPosition() < auton1Rect.yCoordinate + auton1Rect.rectLength))
        {
            autonSelected = 1;
        }
        else if (Brain.Screen.xPosition() > 240 && (Brain.Screen.yPosition() > auton2Rect.yCoordinate && Brain.Screen.yPosition() < auton2Rect.yCoordinate + auton2Rect.rectLength))
        {
            autonSelected = 2;
        }
        else if (Brain.Screen.xPosition() < 240 && (Brain.Screen.yPosition() > auton3Rect.yCoordinate && Brain.Screen.yPosition() < auton3Rect.yCoordinate + auton3Rect.rectLength))
        {
            autonSelected = 3;
        }
        else if (Brain.Screen.xPosition() > 240 && (Brain.Screen.yPosition() > auton4Rect.yCoordinate && Brain.Screen.yPosition() < auton4Rect.yCoordinate + auton4Rect.rectLength))
        {
            autonSelected = 4;
        }

        // printing the current auton route selected
        Brain.Screen.setFillColor(transparent); // set fill color to transparent cuz it could be green from below if statements

        // if statement so if the auton is not 0 (there is an auton), then auton + auton # selected is printed to the brain (instead of none)
        if (autonSelected != 0)
        {
            // print AUTON instead of NONE if an auton is selected
            Brain.Screen.setCursor(11, 19);
            Brain.Screen.print("AUTON");

            // print auton program number to the brain next to AUTON and a space after AUTON
            Brain.Screen.setCursor(11, 25);
            Brain.Screen.print(autonSelected);
        }

        // change the selected auton's rectangle color to green
        if (autonSelected == 1)
        {
            // reset the other auton routes to their color then change this auton route rectangle to green
            // so multiple rectangles might not be green!!!
            initalizeAutonSelector(); // function that will do the above task
            wait(0.1, sec);           // wait time so the rectangles won't flash a different color as well. So computer has time to fill the other rectangles in.

            Brain.Screen.setFillColor(green);
            Brain.Screen.drawRectangle(auton1Rect.xCoordinate, auton1Rect.yCoordinate, auton1Rect.rectWidth, auton1Rect.rectLength);
            Brain.Screen.setCursor(5, 7);
            Brain.Screen.print("AUTON 1");
        }

        else if (autonSelected == 2)
        {
            initalizeAutonSelector();
            wait(0.1, sec);
            Brain.Screen.setFillColor(green);
            Brain.Screen.drawRectangle(auton2Rect.xCoordinate, auton2Rect.yCoordinate, auton2Rect.rectWidth, auton2Rect.rectLength); // x coord, y coord, width, height
            Brain.Screen.setCursor(5, 34);
            Brain.Screen.print("AUTON 2");
        }

        else if (autonSelected == 3)
        {
            initalizeAutonSelector();
            wait(0.1, sec);
            Brain.Screen.setFillColor(green);
            Brain.Screen.drawRectangle(auton3Rect.xCoordinate, auton3Rect.yCoordinate, auton3Rect.rectWidth, auton3Rect.rectLength);
            Brain.Screen.setCursor(9, 7);
            Brain.Screen.print("AUTON 3");
        }

        else if (autonSelected == 4)
        {
            initalizeAutonSelector();
            wait(0.1, sec);
            Brain.Screen.setFillColor(green);
            Brain.Screen.drawRectangle(auton4Rect.xCoordinate, auton4Rect.yCoordinate, auton4Rect.rectWidth, auton4Rect.rectLength);
            Brain.Screen.setCursor(9, 34);
            Brain.Screen.print("AUTON 4");
        }

        // alliance color selection + green rectangle
        if (Brain.Screen.xPosition() > redButton.xCoordinate && Brain.Screen.xPosition() < redButton.xCoordinate + redButton.rectWidth && Brain.Screen.yPosition() < 50 && Brain.Screen.yPosition() > 10)
        {
            allianceColor = "RED";

            // reset other rectangles/buttons
            initalizeAllianceColorSelector();
            wait(0.1, sec);

            // fill in green for selected alliance color
            Brain.Screen.setFillColor(green);
            Brain.Screen.drawRectangle(redButton.xCoordinate, redButton.yCoordinate, redButton.rectWidth, redButton.rectLength);

            // write the "red" text in the button cuz otherwise the green fill will cover it up
            // (don't need to set fill color because the shape will be green anyways)
            Brain.Screen.setCursor(2, 23);
            Brain.Screen.print("RED");

            // fill transparent color so doesn't fill green or something + write color selected
            Brain.Screen.setFillColor(transparent);

            // say which alliance color is selected
            Brain.Screen.setCursor(11, 35);
            Brain.Screen.print("RED");

            // get rid of the "E" from NONE from the default set text for no alliance color selected
            Brain.Screen.setCursor(11, 38);
            Brain.Screen.print(" ");
        }
        else if (Brain.Screen.xPosition() > blueButton.xCoordinate && Brain.Screen.xPosition() < blueButton.xCoordinate + blueButton.rectWidth && Brain.Screen.yPosition() < 50 && Brain.Screen.yPosition() > 10)
        {
            allianceColor = "BLUE";

            // reset other rectangles/buttons
            initalizeAllianceColorSelector();
            wait(0.1, sec);

            // fill in green for selected alliance color
            Brain.Screen.setFillColor(green);
            Brain.Screen.drawRectangle(blueButton.xCoordinate, blueButton.yCoordinate, blueButton.rectWidth, blueButton.rectLength);

            // write the "blue" text in the button cuz otherwise the green fill will cover it up
            // (don't need to set fill color because the shape will be green anyways)
            Brain.Screen.setCursor(2, 33);
            Brain.Screen.print("BLUE");

            // fill transparent color so doesn't fill green or something + write color selected
            Brain.Screen.setFillColor(transparent);

            // say which alliance color is selected
            Brain.Screen.setCursor(11, 35);
            Brain.Screen.print("BLUE");
        }

        wait(0.00001, seconds); // a small wait for the infinite loop
    }
}