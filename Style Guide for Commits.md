#Style Guide for Commit Messages
1 - Messages should be in the past perfect tense.
2 - The head verb of each file desc and should be indicative of what happened in the commit:
    Created - Indicates a file/method was created.
    Developed - Indicates a file was worked on but isn’t finished.
    Finished - Indicates the program is operational, but may still need improvements
    Fixed - Indicates an issue with a file was fixed, error details can be included if important
    Improved - Indicates the program was improved in some way 

3 - At the end of each file description, a file status should be included. This should be done according to section 1.6, and will be further developed and slightly modified here:
    Indev [I] - experimentation, might lack documentation and has a low chance of being included in final code.
    preAlpha [preA] - Things that might make it into the final code but are in very early stages of development, likely unfinished and unable to be compiled yet.
    Alpha [A] - Somewhat functioning code with limited robot functionalities. Untuned if applicable. Framework fully established and can fully be compiled.
    Beta [B] - Mostly finished and tested, may need slight tuning.
    Full Release [FR] - Finished code, may need occasional tuning updates.