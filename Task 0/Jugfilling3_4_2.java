import java.util.ArrayList;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Queue;


public class Jugfilling3_4_2 {

    public static void main(String[] args) {
       State s = new State();
       System.out.println(s.toString());
       BFS startSearch = new BFS();
       startSearch.start(s);
       startSearch.printAllPath();
       //startSearch.printAllPath();
    }
    
}

class BFS {
    Queue<State> queue;
    HashSet<String> visited;
    HashSet<String> explored;
    
    LinkedList<ArrayList<String>> paths;
    ArrayList<String> shortest_path;
    
    public BFS(){
        queue = new LinkedList<>();
        visited = new HashSet<>();
  	explored = new HashSet<>();
        paths = new LinkedList<>();
        shortest_path=new ArrayList<>();
    }
    
    public void printPath(){
        for (String s: shortest_path){
            System.out.println(s);
        }
    }
    
    public void printAllPath(){
        int i=0;
        for (ArrayList<String> list: paths){
            System.out.println("========> " +i);
            for (String s: list){
                System.out.println(s);
            }
            i++;
            
        }
        
    }
    
    public void start(State s){
        queue.add(s);
        State v_list[];
        
        ArrayList<String> r = new ArrayList<>();
        r.add(s.toString());
        paths.add(r);
        
        while(queue.size()!=0){
            State s1 = queue.poll();
            visited.add(s1.toString());
            
            shortest_path = paths.poll();
            
            if(s1.getjug1()== 2 || s1.getjug0()==2){
                System.out.println("Reached");
                System.out.println("Jug0 Jug1");
                return;
            }
            v_list = s1.generateNextState();
            for(State v: v_list){
                if(visited.contains(v.toString())){
                    continue;
                }
		if(explored.contains(v.toString())){
                    continue;
                }
                
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
    private int[] jug;
    
    public State(){
        jug = new int[2];
        jug[0]=jug[1]=0;
    }
    public State(int j0, int j1){
        jug = new int[2];
        jug[0]=j0;
        jug[1]=j1;
    }
    public String toString(){
        return ""+jug[0]+jug[1];
    }
    
    public State[] generateNextState(){
        State states[] = new State[6];
        for (int i=0; i<6; i++){
            states[i] =  new State(jug[0], jug[1]);
        }
        //filling jug 0
        states[0].jug[0] = 3;
        //filling jug 1
        states[1].jug[1] = 4;
        // empty jug 0
        states[2].jug[0] = 0;
        //empty jug 1
        states[3].jug[1] = 0;
        //transfer 0 to 1
        int d = jug[0] + jug[1];
        if(d>4){
            states[4].jug[1]=4;
            states[4].jug[0]=d-4;
        }
        else{
            states[4].jug[0]=0;
            states[4].jug[1]=d;
        }
        
        //transfer 1 to 0
        //int d = jug[0] + jug[1];
        if(d>3){
            states[5].jug[0]=3;
            states[5].jug[1]=d-3;
        }
        else{
            states[5].jug[0]=0;
            states[5].jug[1]=d;
        }        
            
        return states;
        
    }
    
    public int getjug1(){
        return jug[1];
    }
    public int getjug0(){
        return jug[0];
    }
}