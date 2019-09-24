#ifndef DOWNLOAD_STATS_H
#define DOWNLOAD_STATS_H


int elapsedTime(long time, long startTime);

double percentComplete(long bytes, long totalBytes);

double downloadSpeed(long time, long startTime, long bytes);

double totalTime(long time, long startTime, long bytes, long totalBytes);

double remainingTime(long time, long startTime, long bytes, long totalBytes);


#endif
