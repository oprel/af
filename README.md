# Animal Forest - English Translation

This is a work-in-progress translation project for the Nintendo 64 game *Animal Forest*, also known as どうぶつの森 (*Doubutsu no Mori*). It is based on the previous work by [ZoinKity](https://www.romhacking.net/translations/1581/) and the [partial decomp of Animal Forest](https://github.com/zeldaret/af). Since Animal Crossing for the Nintendo Gamecube contains an official translation of almost all of the lines in Animal Forest, we are porting those English lines over to the N64 original.

## Translation Progress
All strings inside the text banks that have an equivalent in Animal Crossing have been [matched](https://github.com/oprel/af/blob/main/link_sheet.csv) (19,500 out of ~20,000 strings/dialogues). Some might need fixing to reflect the functionality of Animal Forest.

### To-do
- [ ] Allow for item names up to 16 characters long.
- [ ] Default to English character input during text input.
- [ ] Translate lines related to the N64 Controller Pak.
- [ ] Inject translated sprites from ZoinKity translation
- [ ] Fix the way time/date are displayed.
- [ ] Fix crash related to mail being longer.
- [ ] Locate and translate Japanese strings not present in the text banks.

### Done
- [x] Extract English text from Animal Crossing (Gamecube).
- [x] Inject English text into banks.
  - Dialogue
  - Items
  - Character Names
  - Mail
  - Misc.
- [x] Support for longer choice strings in dialogue.
- [x] Variable width font.


#### Helping out
I am currently working on this solo, but if you want to help out you can reach me in the [Animal Crossing Modding Discord](https://discord.gg/dRWBVdjYGK)! If you are technically minded and/or have experience decompiling, your help would be most welcome!
