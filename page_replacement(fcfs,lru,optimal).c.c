#include <stdio.h>

int findLRU(int time[], int n) {
    int min = time[0], pos = 0;
    for (int i = 1; i < n; ++i) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int findOptimal(int pages[], int frames[], int n, int f, int index) {
    int farthest = -1, pos = -1, j;
    for (int i = 0; i < f; i++) {
        for (j = index; j < n; j++) {
            if (frames[i] == pages[j]) break;
        }
        if (j == n) return i;
        if (j > farthest) {
            farthest = j;
            pos = i;
        }
    }
    return pos;
}

void fifo(int pages[], int n, int f) {
    int frames[f], front = 0, count = 0, page_faults = 0, page_hits = 0;
    for (int i = 0; i < f; i++) frames[i] = -1;

    printf("\nFIFO Page Faults and Hits:\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                page_hits++;
                break;
            }
        }
        if (!found) {
            frames[front] = pages[i];
            front = (front + 1) % f;
            page_faults++;
        }
    }
    printf("Page Faults: %d\n", page_faults);
    printf("Page Hits: %d\n", page_hits);
}

void lru(int pages[], int n, int f) {
    int frames[f], time[f], counter = 0, page_faults = 0, page_hits = 0;
    for (int i = 0; i < f; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    printf("\nLRU Page Faults and Hits:\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                time[j] = ++counter;
                page_hits++;
                break;
            }
        }

        if (!found) {
            int pos = -1;
            for (int j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    pos = j;
                    break;
                }
            }

            if (pos == -1) pos = findLRU(time, f);
            frames[pos] = pages[i];
            time[pos] = ++counter;
            page_faults++;
        }
    }
    printf("Page Faults: %d\n", page_faults);
    printf("Page Hits: %d\n", page_hits);
}

void optimal(int pages[], int n, int f) {
    int frames[f], page_faults = 0, page_hits = 0;
    for (int i = 0; i < f; i++) frames[i] = -1;

    printf("\nOptimal Page Faults and Hits:\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                page_hits++;
                break;
            }
        }

        if (!found) {
            int pos = -1;
            for (int j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    pos = j;
                    break;
                }
            }

            if (pos == -1) pos = findOptimal(pages, frames, n, f, i + 1);
            frames[pos] = pages[i];
            page_faults++;
        }
    }
    printf("Page Faults: %d\n", page_faults);
    printf("Page Hits: %d\n", page_hits);
}

int main() {
    int pages[100], n, f, choice;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter the page reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &f);

    printf("\n1. FIFO\n2. LRU\n3. Optimal\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            fifo(pages, n, f);
            break;
        case 2:
            lru(pages, n, f);
            break;
        case 3:
            optimal(pages, n, f);
            break;
        default:
            printf("Invalid choice\n");
            return 1;
    }
    return 0;
}
