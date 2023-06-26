rewards = []
actions = []
end_states = []
walls = []
inp = input()
n = int(inp.split(' ')[0])
m = int(inp.split(' ')[1])

def print_float_matrix(arr):
    for i in range(0,n):
        for j in range(0,m):
            print('%.3f' %arr[i][j],end="\t")
        print()

def print_string_matrix(arr):
    for i in range(0,n):
        for j in range(0,m):
            print(arr[i][j],end="\t")
        print()


def getActionReward(i,j,x,y):
    if (x,y) in walls:
        return rewards[i][j]

    if(x == -1 or x == n):
        return rewards[i][j]
    if(y == -1 or y == m):
        return rewards[i][j]

    return rewards[x][y]

def main():
    
    for i in range(0,n):
        row_reward = []
        row_action = []
        row_input = input()
        for j in range(0,m):
            row_reward.append(float(row_input.split(' ')[j]))
            row_action.append('O')
        rewards.append(row_reward)
        actions.append(row_action)
    no_end_states = input()
    no_walls = int(no_end_states.split(' ')[1])
    no_end_states = int(no_end_states.split(' ')[0])
    for i in range(0,no_end_states):
        x = input()
        y = int(x.split(' ')[1])
        x = int(x.split(' ')[0])
        end_states.append((x,y))
    for i in range(0,no_walls):
        x = input()
        y = int(x.split(' ')[1])
        x = int(x.split(' ')[0])
        walls.append((x,y))

    x = input()
    y = float(x.split(' ')[1])
    x = float(x.split(' ')[0])
    start = (x,y)
    unit_step = input()
    unit_step = float(unit_step)

    iterate = True

    # Value Iteration

    while iterate:
        iterate = False
        new_rewards = []
        for i in range(0,n):
            row = []
            for j in range(0,m):
                row.append(-1)
            new_rewards.append(row)

        for i in range(0,n):
            for j in range(0,m):
                if (i,j) in walls:
                    new_rewards[i][j] = rewards[i][j]
                    continue
                if (i,j) in end_states:
                    new_rewards[i][j] = rewards[i][j]
                    continue

                # north
                north = unit_step + float(0.99 * (getActionReward(i,j,i-1,j) * 0.8 + getActionReward(i,j,i,j+1) * 0.1 + getActionReward(i,j,i,j-1) * 0.1))
                # west
                west = unit_step + float(0.99 * (getActionReward(i,j,i,j-1) * 0.8 + getActionReward(i,j,i+1,j) * 0.1 + getActionReward(i,j,i-1,j) * 0.1))
                # east
                east = unit_step + float(0.99 * (getActionReward(i,j,i,j+1) * 0.8 + getActionReward(i,j,i+1,j) * 0.1 + getActionReward(i,j,i-1,j) * 0.1))
                # south
                south = unit_step + float(0.99 * (getActionReward(i,j,i+1,j) * 0.8 + getActionReward(i,j,i,j+1) * 0.1 + getActionReward(i,j,i,j-1) * 0.1))

                action_n_s = action_e_w = 'O'
                max_n_s = max_e_w = 0
                if north >= south: 
                    action_n_s = 'N'
                    max_n_s = north
                else:
                    action_n_s = 'S'
                    max_n_s = south
                if east>=west:
                    action_e_w = 'E'
                    max_e_w = east
                else:
                    action_e_w = 'W'
                    max_e_w = west

                if max_e_w > max_n_s:
                    new_rewards[i][j] = max_e_w
                    actions[i][j] = action_e_w
                else:
                    new_rewards[i][j] = max_n_s
                    actions[i][j] = action_n_s

        # check if optimum achieved 
        for i in range(0,n):
            for j in range(0,m):
                if abs(rewards[i][j]-new_rewards[i][j]) > 0.01  * abs(rewards[i][j]) :
                    iterate = True
        
        # deepcopy doesnot work
        for i in range(0,n):
            for j in range(0,m):
                rewards[i][j] = new_rewards[i][j]

        print_float_matrix(rewards)
        print()
    print_string_matrix(actions)

main()
