//  CS 2505 Fall 2019
//  On my honor:
//  - I have not discussed the C language code in my program with
//    anyone other than my instructor or the teaching assistants
//    assigned to this course.
//
//  - I have not used C language code obtained from another student, 
//    the Internet, or any other unauthorized source, either modified
//    or unmodified.
//
//  - If any C language code or documentation used in my program 
//    was obtained from an authorized source, such as a text book or 
//    course notes, that has been clearly noted with a proper citation
//    in the comments of my program.
//
//  - I have not designed this program in such a way as to defeat or
//    interfere with the normal operation of the grading code.
//  
//    Xander Dyer
//    xdyer@vt.edu
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


int main(int argc, char** argv) {
	
	FILE* input;
    FILE* output;
    char ln[9];
    char ln2[9];
    char lt[9];
    char lt2[9];
    char lnday[4];
    char lnmin[3];
    char lnsec[3];
    char lnd[2];
    char ltday[5];
    char ltmin[4];
    char ltsec[4];
    char ltd[2];
    char ln2day[4];
    char ln2min[3];
    char ln2sec[3];
    char ln2d[2];
    char lt2day[5];
    char lt2min[4];
    char lt2sec[4];
    char lt2d[2];
    int lntots;
    int lttots;
    int ln2tots;
    int lt2tots;
    int dis;
    if (argc < 2) {
		printf("Usage: c02 name of input file> <name of output file>\n \t if no output file is specified one will be generated.");
		return 0;
	}
	input=fopen(argv[1], "r");
	if (argc == 3) {
		output=fopen(argv[2], "w");
	}
	//Default output file when none specified
	else {
		output=fopen("output", "w");
	}
	//Prints header in output file
	fprintf(output, "First coordinate                    Second coordinate                  seconds    DMS\n");
	fprintf(output, "---------------------------------------------------------------------------------------------\n");
	//Scans input until format is not met
	while(fscanf(input, "(%[^,], %[^)])	(%[^,], %[^)])\n", ln, lt, ln2, lt2) == 4) {
		//Stores parts of input variables in new variables for degrees, minutes,
		//seconds and direction.
        sprintf(lnday, "%c%c%c", ln[0], ln[1], ln[2]);
        //Deals with leading 0 on degrees
        if (ln[0] == '0') {
			sprintf(lnday, " %c%c", ln[1], ln[2]);
		}
		sprintf(lnmin, "%c%c", ln[3], ln[4]);
		sprintf(lnsec, "%c%c", ln[5], ln[6]);
		sprintf(lnd, "%c", ln[7]);
		sprintf(ltday, "%c%c", lt[0], lt[1]);
		if (lt[0] == '0') {
			sprintf(lnday, " %c%c", lt[1], lt[2]);
		}
		sprintf(ltmin, "%c%c", lt[2], lt[3]);
		sprintf(ltsec, "%c%c", lt[4], lt[5]);
		sprintf(ltd, "%c", lt[6]);
		fprintf(output, "(%sd %sm %ss %s,  %sd %sm %ss %s)    ", lnday, lnmin, lnsec, lnd, ltday, ltmin, ltsec, ltd);
		sprintf(ln2day, "%c%c%c", ln2[0], ln2[1], ln2[2]);
		sprintf(ln2min, "%c%c", ln2[3], ln2[4]);
		sprintf(ln2sec, "%c%c", ln2[5], ln2[6]);
		sprintf(ln2d, "%c", ln2[7]);
		sprintf(lt2day, "%c%c", lt2[0], lt2[1]);
		sprintf(lt2min, "%c%c", lt2[2], lt2[3]);
		sprintf(lt2sec, "%c%c", lt2[4], lt2[5]);
		sprintf(lt2d, "%c", lt2[6]);
		//Prints formatted output for First and Second coordinates
		fprintf(output, "(%sd %sm %ss %s,  %sd %sm %ss %s)", ln2day, ln2min, ln2sec, ln2d, lt2day, lt2min, lt2sec, lt2d);
        //Stores and converts d/m/s variables in int variables
		lntots = (atoi(lnday)*3600) + (atoi(lnmin)*60) + (atoi(lnsec));
		lttots = (atoi(ltday)*3600) + (atoi(ltmin)*60) + (atoi(ltsec));
		ln2tots = (atoi(ln2day)*3600) + (atoi(ln2min)*60) + (atoi(ln2sec));
	    lt2tots = (atoi(lt2day)*3600) + (atoi(lt2min)*60) + (atoi(lt2sec));
	    //Makes West and South direction coords negative
	    if (ln[7] == 'W') {
			lntots = lntots * -1;
		}
	    if (ln2[7] == 'W') {
			ln2tots = ln2tots * -1;
		}
		if (lt[6] == 'S') {
			lttots = lttots * -1;
		}
	    if (lt2[6] == 'S') {
			lt2tots = lt2tots * -1;
		}
		//Calculates distance between first and second coord using taxi-cab
		dis = abs(lt2tots - lttots) + abs(ln2tots - lntots);
		//Stores and converts distance into DMS format
		char min[4];
		char sec[4];
		int days = dis / 3600;
		int mins = (dis % 3600) / 60;
		int secs = (dis % 3600) % 60;
		//Deals with leading zeros for DMS format
		if (mins > -10 && mins < 10) {
			sprintf(min, "0%d", mins);
		}
		else {
			sprintf(min, "%2d", mins);
		}
		if (secs > -10 && secs < 10) {
			sprintf(sec, "0%d", secs);
		}
		else {
			sprintf(sec, "%2d", secs);
		}
		//Deals with formatting for different distance lengths when printing
		if (dis < 10) {
			fprintf(output, "       %d     ", dis);
		}
		if (dis < 100 && dis > 10) {
			fprintf(output, "      %d     ", dis);
		}
		if (dis < 1000 && dis > 100) {
			fprintf(output, "     %d     ", dis);
		}
		if (dis < 10000 && dis > 1000) {
			fprintf(output, "    %d     ", dis);
        }
        if (dis > 10000) {
			fprintf(output, "   %d     ", dis);
		}
		//Prints DMS format
		fprintf(output, " %dd %sm %ss\n", days, min, sec);
	}
	
	

}


