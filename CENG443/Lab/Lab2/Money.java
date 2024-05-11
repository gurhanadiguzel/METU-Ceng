import java.util.concurrent.*;

class WithdrawTask implements Runnable{
    Buffer buffer;
    public WithdrawTask(Buffer buffer){
        this.buffer = buffer;
    }

    @Override
    public void run() {
        try {
            while (true) {
                int money = (int)(Math.random() * 100);
                buffer.withdraw(money);
                if(buffer.totalMoney >= money){
                    buffer.totalMoney -= money;
                    System.out.println("Withdraw\t" + money + "\t\t" + buffer.totalMoney);
                }else {
                    System.out.println("Cannot Withdraw\t" + money+ "\t\t" + buffer.totalMoney);
                }
                Thread.sleep(100);
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
} 

class DepositTask implements Runnable{
    Buffer buffer;
    public DepositTask(Buffer buffer){
        this.buffer = buffer;
    }

    @Override
    public void run() {
        try {
            while (true) {
                int money = (int)(Math.random() * 100);
                buffer.deposit(money);
                Thread.sleep(100);
                buffer.totalMoney += money;
                System.out.println("Deposit\t\t" + money+ "\t\t" + buffer.totalMoney);
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
} 



class Buffer {
    private BlockingQueue<String> list;
    public int totalMoney;
     
    public Buffer(){
        this.totalMoney = 0;
        this.list = new LinkedBlockingQueue<>(1);
    }

    public void withdraw(int money)throws InterruptedException{
        list.take();
    }

    public void deposit(int money)throws InterruptedException{
        list.put(" ");
    }
}


class Money {
    public static void main(String[] args) throws InterruptedException{
        Buffer buffer = new Buffer();
        ExecutorService taskList =  Executors.newFixedThreadPool(2);
        taskList.execute(new WithdrawTask(buffer));
        taskList.execute(new DepositTask(buffer));
        
        taskList.shutdown();
  
    }
    
}
