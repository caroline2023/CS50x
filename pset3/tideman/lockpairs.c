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
        for (int i = 0; i < candidate_count; i++)
            //set everything in losers[candidate_count] array to -1 before starting so later with the in_arr func
        {
            losers[i] = -1;
        }
        int x = 0;
        int y = 0;
        int z = 0;
        /*let there be some x that starts at 0 and goes up every time we add new person to it
        and y to mark the x that was in the previous loop
        and z to mark the x after a loop 
        basically after 1 loop x goes up. z keeps track of its value at the start of the loop
        then y takes on z after the loop is executed and z takes on the value of x */
        bool in_array(int num)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (losers[i] == num)
                {
                    return true;
                }
            }
            return false;
        }
        
        for (int a = 0; a < candidate_count; a++)
        {
            for (int i = y; i < x; i++)
            {
                for (int j = 0; j < candidate_count; j++)
                {
                    if locked[i][j] = true
                    {
                        losers[x] = j;
                        x++;
                    }
                }
                y = z;
                z = x;
            }
            if (in_array(pairs[i].winner))
            {
                cycle = true;
                break;
            }
            else if (y = x) //basically in this case no new elements were added
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