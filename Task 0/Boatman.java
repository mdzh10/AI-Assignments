import java.util.ArrayList;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Queue;

public class Boatman {

    public static void main(String[] args) {
        State s = new State();
        // System.out.println(s.toString());
        BFS startSearch = new BFS();
        startSearch.start(s);
        startSearch.printPath();
        // startSearch.printAllPath();
    }

}

class BFS {
    Queue<State> queue;
    HashSet<String> visited;
    HashSet<String> explored;

    LinkedList<ArrayList<String>> paths;
    ArrayList<String> shortest_path;

    public BFS() {
        queue = new LinkedList<>();
        visited = new HashSet<>();
        explored = new HashSet<>();
        paths = new LinkedList<>();
        shortest_path = new ArrayList<>();
    }

    public void printPath() {
        for (String s : shortest_path) {
            System.out.println(s);
        }
        System.out.println("Reached");
    }

    public void printAllPath() {
        int i = 0;
        for (ArrayList<String> list : paths) {
            System.out.println("========> " + i);
            for (String s : list) {
                System.out.println(s);
            }
            i++;

        }

    }

    public void start(State s) {
        queue.add(s);
        State v_list[];

        ArrayList<String> r = new ArrayList<>();
        r.add(s.toString());
        paths.add(r);

        while (queue.size() != 0) {
            State s1 = queue.poll();
            visited.add(s1.toString());
            // s1.print("s1");
            shortest_path = paths.poll();
            // int num;

            if (s1.getf() == 1 && s1.getg() == 1 && s1.getc() == 1 && s1.getw() == 1) {
                return;
            }
            v_list = s1.generateNextState();

            for (State v : v_list) {
                // System.out.println("num = " + num);
                // num++;
                if (visited.contains(v.toString())) {
                    continue;
                }
                if (explored.contains(v.toString())) {
                    continue;
                }
                // v.print("v");
                // System.out.println(v);
                queue.add(v);
                explored.add(v.toString());
                ArrayList<String> r1 = new ArrayList<>(shortest_path);
                r1.add(v.toString());
                paths.add(r1);
            }
        }
    }
}

class State {
    public int[] boat;

    // boat(0)--f
    // boat(1)--g
    // boat(2)--c
    // boat(3)--w

    public State() {
        boat = new int[4];
        boat[0] = boat[1] = boat[2] = boat[3] = 0;
    }

    /*
     * void print(String s) { System.out.println(s + " : "); for (int i = 0; i < 4;
     * i++) { System.out.println(i + " = " + boat[i]); } }
     */

    public State(int i, int j, int k, int l) {
        boat = new int[4];
        boat[0] = i;
        boat[1] = j;
        boat[2] = k;
        boat[3] = l;
    }

    public String toString() {
        return "" + boat[0] + boat[1] + boat[2] + boat[3];
    }

    public State[] generateNextState() {

        State states[] = new State[4];
        for (int i = 0; i < 4; i++) {
            states[i] = new State(boat[0], boat[1], boat[2], boat[3]);
        }

        if ((boat[1] == boat[2] && boat[0] != boat[1]) || (boat[1] == boat[3] && boat[0] != boat[1]))
            return states;

        if (boat[0] == 0) {
            // farmer crosses
            states[0].boat[0] = 1;
            // farmer and goat crosses
            if (boat[1] == 0) {
                states[1].boat[0] = 1;
                states[1].boat[1] = 1;
            }
            // farmer and cabbage crosses
            if (boat[2] == 0) {
                states[2].boat[0] = 1;
                states[2].boat[2] = 1;
            }
            // farmer and wolf crosses
            if (boat[3] == 0) {
                states[3].boat[0] = 1;
                states[3].boat[3] = 1;
            }

        } else {
            // farmer returns
            states[0].boat[0] = 0;
            // farmer and goat returns
            if (boat[1] == 1) {
                states[1].boat[0] = 0;
                states[1].boat[1] = 0;
            }
            // farmer and cabbage returns
            if (boat[2] == 1) {
                states[2].boat[0] = 0;
                states[2].boat[2] = 0;
            }
            // farmer and wolf returns
            if (boat[3] == 1) {
                states[3].boat[0] = 0;
                states[3].boat[3] = 0;
            }

        }

        return states;
    }

    public int getf() {
        return boat[0];
    }

    public int getg() {
        return boat[1];
    }

    public int getc() {
        return boat[2];
    }

    public int getw() {
        return boat[3];
    }

}