# Mannual_Section-Injection



This was a small lab aimed at injecting shell code inside a PE header.
The aim was to inject shell code into the shift control from the Original EP to the address of my shell code and execute it and move control back to the original EP and make it look like nothing had happened
First i created main.cpp, ran it to get main.exe, my PE then usnig x32dbg i analyzed the Assembly(JK just pressed F9 a couple of times :) ) and found the EP(Entry Point).
From here i saved its address ann looked for a code cave to inject my shell code later found that the shell code was not sufficient (1) hence i had to now make a new section.
I opened CFF explorer PE editor Hex workstation and got to work. from CFF explorer and PE editor i found the size and number of the total Sections. i also found the section and file allignments that helped me in creating the new section.
In Hex workstation i found the 50 45 magic words for the PE header and found an empty spot to create a new section. 
I copied some empty bytes and pasted them into the end of the PE which would act as the peice of memory for the new section, then i noted down the starting address and the size of the Code Cave (The empty bytes i just added) and i wrote the necessary bytes into the place for the new section
To fix up the PE Header, i added the three following things:
- Increased the number of sections (which is at offset 06 in the PE Header!)
- Increase Image Size (which is at offset 50 in the PE header)
- Add our new section to the section table

I saw that the number of sections in the hex editor is 0D which accounts to 13 sections also in CFF explorer i see that there are 13 sections. So i changed D to E.
At offset 50 i saw 00 10 01 00 which is currently in little endian and is equal to 00011000. i changed it to 00012000 (00 20 01 00)bcz the allignmemt size acc to CFF is 1000 so a new section would mean the image size inc by 1000. 

Following are the changes i made to the new section memory bytes after allocating the address where i wanted to add the new section

Offset  Description
+0      Name
+08     PhysicalAddress / Virtual Size (Size in bytes of the Code Cave)
+0C     VirtualAddress  (Starting Address of the New Section)
+10     SizeOfRawData  (Size of Code Cave)
+14     PointerToRawData  (Address of start of Code Cave)
+18     PointerToRelocations  (leave empty)
+1C     PointerToLineNumbers  (leave empty)
+20     NumberOfRelocations   (leave empty)
+22     NumberOfLineNumbers   (leave empty)
+24     Characteristics  (Such as C0000040 (like .data section) -> 400000C0 ) this wil give the section perms like execute read write.

Later i checked in CFF and the new section was showing
I opened x32dbg (Again :) ) and located the new Sections Code Cave pushed the AD and FD flags onto the stack in order to store the registers data on the stack to pop later. the purpose was so that when the shell code makes changes to the registers they can be reverted back to their original state before shifting control back to the original EP.
Then i added the shell code and popped the AD AF flags thus restoring the registers back to their original States
Then added the addresse of the EP and the PE was ready

Challenges Encountered:
1. The code cave i initially found wasnt sufficient bcz the offsets were included in the stack they were dynamically allocated. so after googling around the only possible sol was to create a new section that could have enough empty offsets to run my shell code.
2. The Shell code i added was corrupt for some reason. it tried to access an empty eax register which resulted in the dubugger giving an error and not executing further. Sadly i was too worn out to add a new shell code to it hance i just left it as it was and had to move onto the next proj. Perhaps ill have a look at it in the future
