import java.util.Random;

public class Nqueen {

    public static void main(String[] args) {

        //initial State
        State s = new State(4);  //param 4 for 4-Queen problem, 8 for 8-queen problem
        s.printBoardInfo();
        s.printBoard();
        
        // Solving using Random restart hill climbing
        HillClimbing hc = new HillClimbing(50);        
        State g = hc.randomRestart(s);
        
        // solution
        g.printBoardInfo();
        g.printBoard();          
    }

}

class Queen {
    private int row;
    private int col;

    public Queen(int row, int col) {
        this.row = row;
        this.col = col;
    }
    public int getRow() {
        return row;
    }   
    public int getCol() {
        return col;
    }

    public void setRow(int row) {
        this.row = row;
    }
    
    public void moveTo(int bound){
        row++;
        if(row == bound) row = 0;
    }
    
    public boolean isAttacking(Queen q){
        
        if(row == q.row || col==q.col)
            return true;
        else if(Math.abs(row-q.row) == Math.abs(col-q.col))
            return true;
        else 
            return false;        
        
    }
    
    @Override
    public String toString(){
        return "("+row+","+col+")";
    } 
    
}


class State {
    private Queen[] queens;
    private int n_queen;
    private int totalPairOfAttack;
    
    public State() {
        this.queens = new Queen[4];
        totalPairOfAttack = 99;
        n_queen = 4;
    }
    public State(int n) {
        this.queens = new Queen[n];
        Random rand = new Random();
        for (int i = 0; i < n; i++) {
            queens[i] = new Queen(rand.nextInt(n), i);
        }
        n_queen = n;
        totalPairOfAttack = countTotalAttack();
    }   
    
    public State(State s){
        this.queens = new Queen[s.n_queen];
        n_queen = s.n_queen;        
        for (int i = 0; i < s.n_queen ; i++) {
            queens[i] = new Queen(s.queens[i].getRow(), s.queens[i].getCol());
        }
        totalPairOfAttack = s.totalPairOfAttack;
    }
    
    private int countTotalAttack() {
        int count = 0;
        for (int i = 0; i < n_queen; i++) {
            for (int j = i + 1; j < n_queen; j++) {
                if (queens[i].isAttacking(queens[j])) {
                    count++;
                }
            }
        }
        return count;
    }
    public void printBoard() {
        int temp[][] = new int[n_queen][n_queen];
        for (int i = 0; i < n_queen; i++) {
            temp[queens[i].getRow()][queens[i].getCol()] = 1;
        }
        for (int i = 0; i < n_queen; i++) {
            for (int j = 0; j < n_queen; j++) {
                System.out.print(temp[i][j]+" ");
            }
            System.out.println("");      
        }
        System.out.println("");
        
    }
    public void printBoardInfo() {
        for (int i = 0; i < n_queen; i++) {
            System.out.print(queens[i].toString() + " ");
        }
        System.out.print(" val: " + totalPairOfAttack);
        System.out.println("");
    }    
    public int getTotalPairOfAttack() {
        return totalPairOfAttack;
    }
    public int getN_queen() {
        return n_queen;
    }
    
    public State generateBestState() {  
              
        State best = new State(this);    
        
        for (int i = 0; i < n_queen; i++) { // selecting each queen 
            State temp = new State(this);
            for (int j = 0; j < n_queen; j++) { // moves to be given by each queen                
                temp.queens[i].moveTo(n_queen);
                temp.totalPairOfAttack = temp.countTotalAttack();
                
                if (best.totalPairOfAttack > temp.totalPairOfAttack) { // temp is better than best
                    best = new State(temp);                   
                    best.totalPairOfAttack = best.countTotalAttack();
                }
            }
        }
        return best;
    }
}

class HillClimbing {

    private int sigma;

    public HillClimbing(int sigma) {
        this.sigma = sigma;
        
    }
    public State simpleStart(State start) {
        State current = new State(start);        
        int countSigma = 0;
        
        while (true) {
            State best = current.generateBestState();

            if (best.getTotalPairOfAttack() < current.getTotalPairOfAttack()) {
                current = new State(best);
            }
            if (countSigma == sigma) {
                break;
            }
            countSigma++;
        }

        return current;
    }
    public State randomRestart(State start){
        State goal;
        int restart=0;
        
        while (true) {
            goal = simpleStart(start);

            if (goal.getTotalPairOfAttack() == 0) {
                break;
            }
            restart++;
            start = new State(start.getN_queen());
        }
        System.out.println("Restart needed: " + restart);        
        return goal;
    }
}
