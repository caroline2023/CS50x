#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i; // for the (rank)th entry in the array, insert candidate index
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++) //to loop over the less preferred peeps
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++) //so that we won't overcount
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair newpairs[pair_count];
    int n = 0; //to use in loop to find greatest difference btw winner and loser
    int m = 42; //upper bound so we don't repeat. n is lower bound
    //for that it would be better to use voter_count except it aint a global variable
    int x = 0; //x determines its index in newpairs
    int win;

    for (int i = 0; i < pair_count; i++) //have to loop through at least pair_count times
    {
        for (int j = 0; j < pair_count; j++)
        {
            win = preferences[pairs[j].winner][pairs[j].loser];
            //oh right we only need to how how many prefer x over y and that uniquely determines how many prefer y over x
            if (n < win && win < m) //the m needs to be there so we wont keep repeating the same values when sorting
            {
                n = win;
            }
        }

        m = n;
        for (int j = 0; j < pair_count; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] == m)
                //find the pairs such that one has a preference of m over the other and add them to new pairs
            {
                newpairs[x] = pairs[j];
                x++;
            }
        }

        n = 0;
    }

    for (int i = 0; i < pair_count; i++)
    {
        pairs[i] = newpairs[i]; //changing the pairs thing to match the sorted array
    }

    return;
}

bool in_array(int num, int arr[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (arr[i] == num)
        {
            return true;
        }
    }

    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    for (int i = 0; i < pair_count; i++)
    {
        bool cycle = false; //if its false that means adding this won't create a cycle

        int losers[candidate_count];
        for (int j = 0; j < candidate_count; j++)
            //set everything in losers[candidate_count] array to -1 before starting so later with the in_arr func
        {
            losers[j] = -1;
        }
        int x = 0;
        int y = 0;
        int z = 0;
        /*let there be some x that starts at 0 and goes up every time we add new person to it
        and y to mark the x that was in the previous loop
        and z to mark the x after a loop
        basically after 1 loop x goes up. z keeps track of its value at the start of the loop
        then y takes on z after the loop is executed and z takes on the value of x */

        //we have to fill the array first
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[pairs[i].loser][j] == true)
            {
                losers[x] = j;
                x++;
            }
        }

        z = x;

        for (int a = 0; a < candidate_count; a++)
        {
            for (int j = y; j < x; j++)
            {
                for (int k = 0; k < candidate_count; k++)
                {
                    if (locked[losers[j]][k] == true)
                    {
                        losers[x] = k;
                        x++;
                    }
                }

                y = z;
                z = x;
            }

            if (in_array(pairs[i].winner, losers))
            {
                cycle = true;
                break;
            }
            else if (y == x) //basically in this case no new elements were added
            {
                break;
            }
        }

        if (cycle == false)
        {
            locked[pairs[i].winner][pairs[i].loser] = true; //then we can add this into the graph
        }
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    //ok so basically the only candidate with no false in their column
    for (int i = 0; i < candidate_count; i++)
    {
        bool x = true;

        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                x = false;
            }
        }

        if (x == true)
        {
            printf("%s\n", candidates[i]);
        }
    }

    return;
}

