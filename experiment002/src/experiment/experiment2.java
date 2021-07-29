package experiment;


import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.*;
/*
 *(1)产生式集合
 *(2)first和follower集合
 **/

public class experiment2 {
    //first集合
    public static HashMap<String, HashSet<String>> first = new HashMap<>();

    //firstX集合，指任意符号串的first集合
    public static HashMap<String, HashSet<String>> firstX = new HashMap<>();

    //follower集合
    public static HashMap<String, HashSet<String>> follower = new HashMap<>();

    //文法的开始符
    public static String start = "S";

    //存储非终结符的集合
    public static HashSet<String> VnSet = new HashSet<>();

    //存储终结符的集合
    public static HashSet<String> VtSet = new HashSet<>();

    //存储每个非终结符的产生式
    public static HashMap<String, ArrayList<String>> outputSet = new HashMap<>();

    //分析表
    public static String[][] analysis_table;

    //分析栈
    public static Stack<String> Ana_stack = new Stack<>();

    //记录动作
    public static String active = "";

    //记录分析步数
    public static int index = 0;

    //源程序
    public static String source = "id = id * id $";

    //文件路径
    public static String PATH = "D:\\Desktop\\homework\\experiment002\\src\\experiment\\readin.txt";
    public static int rows = 8;
    public static String PATH1 = "D:\\Desktop\\homework\\experiment002\\src\\experiment\\readin1.txt";
    public static int rows1 = 8;

    public static String getSource_PATH = "D:\\Desktop\\homework\\experiment002\\src\\experiment\\source.txt";

    //读入文件
    public static String[] grammar = getSource();

    public static String[] getSource() {
        FileInputStream inputStream = null;
        BufferedReader bufferedReader = null;
        String str;
        String[] grammar = new String[rows];
        int num = 0;
        try {
            inputStream = new FileInputStream(PATH);
            bufferedReader = new BufferedReader(new InputStreamReader(inputStream));
            while ((str = bufferedReader.readLine()) != null) {
                grammar[num] = str;
                num++;
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (inputStream != null) {
                    inputStream.close();
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
            try {
                if (bufferedReader != null) {
                    bufferedReader.close();
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        return grammar;
    }

    //初始化
    public static void Init() {
        for (String s : grammar) {
            String[] str = s.split("->");//通过“->”分隔文法
            String left = str[0];
            //判断outputSet中是否有左部，若有，通过get方法得到，若没有，新建一个ArrayList
            ArrayList<String> list;
            if (outputSet.containsKey(left)) {
                list = outputSet.get(left);
            } else {
                list = new ArrayList<>();
            }
            list.add(str[1]);
            outputSet.put(left, list);
        }

        for (String left : VnSet) {
            HashSet<String> element = new HashSet<>();
            follower.put(left, element);
        }

        //求非终结符的first集
        for (String left : VnSet) {//遍历所有左部（非终结符）
            getFirst(left);
        }

        //求每个产生式的firstX集
        for (String left : VnSet) {
            ArrayList<String> right = outputSet.get(left);
            for (String Generational : right) {
                getFirstX(Generational);
            }
        }

        //求非终结符的follower集
        getFollower();

        //构造分析表
        create_analysis_table();

        //初始化栈
        Ana_stack.push("$");
        Ana_stack.push(start);
    }

    //构造分析表
    private static void create_analysis_table() {
        //终结符数组
        Object[] VtArray = VtSet.toArray();
        //非终结符数组
        Object[] VnArray = VnSet.toArray();

        //初始化预测分析表
        analysis_table = new String[VnArray.length + 1][VtArray.length + 1];
        analysis_table[0][0] = "分析表";
        //初始化分析表
        //初始化首行
        for (int i = 0; i < VtArray.length; i++)
            analysis_table[0][i + 1] = (Objects.equals(VtArray[i].toString(), "@")) ? "$" : VtArray[i].toString();
        //初始化首列
        for (int i = 0; i < VnArray.length; i++)
            analysis_table[i + 1][0] = VnArray[i].toString();
        //初始化分析表，全部置为error
        for (int i = 0; i < VnArray.length; i++) {
            for (int j = 0; j < VtArray.length; j++) {
                analysis_table[i + 1][j + 1] = "error";
            }
        }

        //分析表构造
        //遍历所有非终结符
        for (String left : VnSet) {
            //得到所有产生式
            ArrayList<String> right = outputSet.get(left);
            //遍历产生式
            for (String Generational : right) {
                //得到该产生式的first
                HashSet<String> firstSet = firstX.get(Generational);
                //first表有的全部插入insert(非终结符， 终结符， 产生式)
                for (String value : firstSet) {
                    insert(left, value, Generational);
                }
                //如果first中包含空，则将follower中的元素也加入进构造表中
                if (firstSet.contains("@")) {
                    HashSet<String> followerSet = follower.get(left);
                    for (String value : followerSet) {
                        insert(left, value, Generational);
                    }
                }
            }
        }
    }

    private static void insert(String left, String value, String generational) {
        if (Objects.equals(value, "@"))
            value = "$";
        for (int i = 1; i < VnSet.size() + 1; i++) {
            if (Objects.equals(analysis_table[i][0], left)) {
                for (int j = 1; j < VtSet.size() + 1; j++) {
                    if (Objects.equals(analysis_table[0][j], value)) {
                        analysis_table[i][j] = generational;
                        return;
                    }
                }
            }
        }
    }

    //取出终结符和非终结符的集合
    public static void getVnVt() {
        for (String strs : grammar) {
            //将一个产生式用->分割开
            String[] str = strs.split("->");
            //str[0]为非终结符，加入到VnSet中
            VnSet.add(str[0]);
        }
        for (String strs : grammar) {
            //将一个产生式用->分割开
            String[] str = strs.split("->");
            //str[1]为产生式，通过split(" ")分割，每个元素判断是否在非终结符表里，若不在，则加入终结符表中
            String[] right = str[1].split(" ");
            for (String vtSet : right) {
                if (!VnSet.contains(vtSet)) {
                    VtSet.add(vtSet);
                }
            }
        }
    }

    public static void getFirst(String left) {
        /*
         * 如果X为终结符,First(X)=X；
         * 如果X->ε是产生式，把ε加入First(X)；
         * 如果X是非终结符，如X->YZW。从左往右扫描产生式右部，把First(Y)加入First(X)；
         * 如果First(Y)不包含ε，表示Y不可为空，便不再往后处理；如果First(Y)包含ε，表示Y可为空，则处理Z，依次类推。
         */
        //得到对应起始符的产生式的集合
        ArrayList<String> list = outputSet.get(left);
        //判断first中是否有起始符c的键值对,若有则说明该元素first已求出，若没有，则创建一个
        HashSet<String> set;
        if (first.containsKey(left)) {
            return;

        } else {
            set = new HashSet<>();
        }
        //遍历所有产生式
        for (String right : list) {
            //如果产生式为空，则将空加入first中
            if (Objects.equals(right, "@")) {//s->@
                set.add("@");
                break;
            } else {
                //如果产生式不为空，则使用split(" ")将产生式分割为一个个元素进行遍历
                String[] element = right.split(" ");
                for (int i = 0; i < element.length; i++) {
                    //如果该符号是终结符，那么将该符号加入first中，退出循环
                    if (VtSet.contains(element[i])) {
                        set.add(element[i]);
                        break;
                    }
                    //如果该符号是非终结符，那么获取该非终结符的first将其赋给自己的first
                    if (VnSet.contains(element[i])) {
                        //拿该终结符的first前先对其初始化
                        getFirst(element[i]);
                        //得到该终结符的first集合
                        if (first.containsKey(element[i])) {
                            HashSet<String> vtSet = first.get(element[i]);
                            //将该非终结符的first加入自己的first集合中
                            set.addAll(vtSet);
                            //判断该非终结符的first中是否包含空
                            if (!vtSet.contains("@")) {
                                //如果不包含空串，则处理下一个产生式
                                break;
                            }
                        }
                    }
                    i++;
                }
            }
        }
        first.put(left, set);
    }

    public static void getFirstX(String c) {
        /*
          构造任意文法符号串的first集，如：X->YZW；求YZW的first集
          从左往右扫描该式，加入其非空first集：把First(Y)加入First(YZW)
          若包含空串，处理下一个符号：如果First(Y)包含空串，便处理Z；不包含就退出.
          处理到尾部，即所有符号的first集都包含空串 把空串加入First(YZW)。
         */
        //判断firstX中是否有文法c的键值对,若有，则使用firstX中的hashSet，若没有，则创建一个
        HashSet<String> set;
        if (firstX.containsKey(c)) {
            return;
        } else {
            set = new HashSet<>();
        }
        String[] str = c.split(" ");
        int i = 0;
        //follower调用过来时，第一个会有空字符，所以要跳过
        if (Objects.equals(str[0], "")){
            i = 1;
        }
        while (i <= str.length - 1){
//        for (int i = 1; i <= str.length - 1; i++) {
            //如果该符号是终结符，那么将该符号加入first中,退出循环
            if (VtSet.contains(str[i])) {
                set.add(str[i]);
                break;
            }
            //如果该符号是非终结符，那么将该非终结符的first集合加入到该文法符号串的first集合中
            if (VnSet.contains(str[i])) {
                //得到该非终结符的first集合
                HashSet<String> firstSet = first.get(str[i]);
                //将first集合加入该文法的firstX中
                set.addAll(firstSet);
                //判断该非终结符的first中是否包含空
                if (!firstSet.contains("@")) {
                    //如果不包含，则退出循环
                    break;
                }
            }
            i++;
        }
        firstX.put(c, set);
    }

    public static void getFollower() {
        /*
         * (1)$属于FOLLOW(S)，S是开始符；
         * (2)查找输入的所有产生式，确定X后紧跟的终结符；
         * (3)如果存在A->αBβ，（α、β是任意文法符号串，A、B为非终结符），把first(β)的非空符号加入follow(B)；
         * first(β)由firstX求得
         * (4)如果存在A->αB或A->αBβ 但first(β)包含空，把follow(A)加入follow(B)。
         * 综上，有4种情况
         * 1、若A->αBaβ，（α、β是任意文法符号串，A、B为非终结符，a为终结符），则a加入follower（B）
         * 以此为例A->αBβ，（α、β是任意文法符号串，A、B为非终结符）
         * 2、若β不存在，即B是最后一个符号，则follower（A）加入到follower（B）
         * 3、若β存在，则将first（β）- 空 加入到follower（B）
         * 4、在3的基础上，若first（β）存在空元素，则将follower（A）加入到follower（B）
         */
        //A->αBβ
        HashSet<String> setA;//key的follower集合的set
        HashSet<String> setB;//B的follower集合的set
        HashSet<String> setC;//β的first集合的set
        //给起始符添加$元素
        setA = new HashSet<>();
        setA.add("$");
        follower.put(start, setA);
        //遍历所有产生式
        //得到所有非终结符，作为outputSet的key来拿到所有产生式
        //flag用来判断follower集合是否有变动
        boolean flag = true;
        while (flag) {
            //先将flag置为false，若下面操作中有put操作，则说明follower有变动，将flag置为true再次循环
            flag = false;
            for (String left : VnSet) {
                //通过key得到产生式集合,遍历产生式集合，得到每一个产生式
                ArrayList<String> Generationals = outputSet.get(left);
                for (String Generational : Generationals) {
                    //把产生式通过split分割，得到所有元素，遍历分析各种情况下如何添加follower元素
                    String[] element = Generational.split(" ");
                    int i = element.length - 1;
                    //存储任意文法符号串，以方便通过firstX求得该文法符号串的first
                    String B = "";
                    while (i >= 0) {//倒序遍历
                        //若该元素是终结符，且前一个符号是非终结符，则将该符号加入到前一个符号的follower中
                        //A -> ...Ba...
                        if ((VtSet.contains(element[i])) && ((i - 1) >= 0) && (VnSet.contains(element[i - 1]))) {
                            //得到B的follower集合中的hashSet
                            setB = follower.get(element[i - 1]);
                            //如果steB中有这个元素，那么直接跳过
                            if (!setB.contains(element[i])) {
                                //如果steB中没有这个元素，则put到follower（B）中，且表进行了更新，将flag置为true
                                setB.add(element[i]);
                                follower.put(element[i - 1], setB);
                                flag = true;
                            }
                            B = " " + element[i] + B;
                            i--;
                            continue;
                        }
                        //若该元素为非终结符，且此元素为最后的一个元素
                        //A->...B
                        //则将A的follower加入到B中
                        if (i == element.length - 1 && VnSet.contains(element[i])) {
                            //得到A，B的follower对应的hashSet
                            setA = follower.get(left);
                            setB = follower.get(element[i]);
                            //如果steA的size=0，说明setA为空，避免空指针异常，直接跳过
                            if (setA.size() != 0) {
                                //说明setA有值，遍历setA中的所有元素
                                for (String value : setA) {
                                    //如果setA中的值setB中也有，则跳过，如果没有则put，且表进行了更新，将flag置为true
                                    if (!setB.contains(value)) {
                                        setB.add(value);
                                        follower.put(element[i], setB);
                                        flag = true;
                                    }
                                }
                            }
                        }
                        //若该元素不为最后一个元素，且该元素为非终结符
                        //A->...Bβ(β为任意文法符号串
                        if (VnSet.contains(element[i]) && element.length - 1 - i > 0) {
                            //将first（B）加入followerB中，得到β的first集合，得到其对应的hashSet表
                            getFirstX(B);
                            setC = firstX.get(B);
                            //得到B对应follower的hashSet表
                            setB = follower.get(element[i]);
                            //将β的first集合的非空元素加入到followerB中
                            for (String s : setC) {
                                //判断该元素是否为空，且该元素在followerB中是否存在
                                if (!Objects.equals(s, "@") && !setB.contains(s)) {
                                    //若不存在该元素，则将该元素加入到followerB中，且表进行了更新，将flag置为true
                                    setB.add(s);
                                    follower.put(element[i], setB);
                                    flag = true;
                                }
                            }
                            //若该符号串的first中有空，则，将follower（A）加入到follower（B）中
                            if (setC.contains("@")) {
                                //得到followerA的hashSet
                                setA = follower.get(left);
                                //如果steA的size=0，说明setA为空，避免空指针异常，直接跳过
                                if (setA.size() != 0) {
                                    //说明setA有值，遍历setA中的所有元素
                                    for (String value : setA) {
                                        //如果setA中的值setB中也有，则跳过，如果没有则put，且表进行了更新，将flag置为true
                                        if (!setB.contains(value)) {
                                            setB.add(value);
                                            follower.put(element[i], setB);
                                            flag = true;
                                        }
                                    }
                                }
                            }
                        }
                        //将该元素加入到B中
                        B = " " + element[i] + B;
                        i--;
                    }
                }
            }
        }
    }

    public static void analysis() {
        System.out.println("-------------------1.LL分析过程-------------------");
        System.out.println("|               分析栈              输入串            动作|  ");
        print_process(source);
        String X = Ana_stack.peek();
        String[] value = source.split(" ");
        while (!X.equals("$")) {
            if (X.equals(value[index])) {
                active = "匹配 " + Ana_stack.peek();
                Ana_stack.pop();
                index++;
            } else if (VtSet.contains(X)) {
                return;
            } else if (find(X, value[index]).equals("error")) {
                return;
            } else if (find(X, value[index]).equals("@")) {
                Ana_stack.pop();
                active = X + "->@";
            } else {
                String match = find(X, value[index]);
                if (!match.equals("")) {
                    active = X + "->" + match;
                    Ana_stack.pop();
                    String[] s = match.split(" ");
                    for (int i = s.length - 1; i >= 0; i--) {
                        Ana_stack.push(s[i]);
                    }
                } else {
                    System.out.println("error at " + value[index] + " in " + index);
                    return;
                }
            }
            String str = "";
            for (int i = index; i < value.length; i++) {
                str = str + " " + value[i];
            }
            X = Ana_stack.peek();
            print_process(str);
        }
    }

    public static void print_process(String str) {
        System.out.printf("%22s", Ana_stack);
        System.out.printf("%20s", str);
        System.out.printf("%16s", active);
        System.out.println();
    }

    public static String find(String X, String a) {
        for (int i = 0; i < VnSet.size() + 1; i++) {
            if (analysis_table[i][0].equals(X)) {
                for (int j = 0; j < VtSet.size() + 1; j++) {
                    if (analysis_table[0][j].equals(a)) {
                        return analysis_table[i][j];
                    }
                }
            }
        }
        return "";
    }

    public static void printAll() {
        System.out.println("----------------------------------------文法----------------------------------------");
        for (String key : VnSet) {
            System.out.print(key + "\t->\t");
            for (String str : outputSet.get(key)) {
                System.out.print(str + "\t|\t");
            }
            System.out.println();
        }
        System.out.println("----------------------------------------文法----------------------------------------");
        System.out.println("----------------------------------------非终结符----------------------------------------");
        System.out.print("VnSet : ");
        for (String vnSet : VnSet) {
            System.out.print(vnSet + "\t");
        }
        System.out.println();
        System.out.println("----------------------------------------非终结符----------------------------------------");
        System.out.println("----------------------------------------终结符----------------------------------------");
        System.out.print("VtSet : ");
        for (String vtSet : VtSet) {
            System.out.print(vtSet + "\t");
        }
        System.out.println();
        System.out.println("----------------------------------------终结符----------------------------------------");
        System.out.println("----------------------------------------first----------------------------------------");
        for (String key : VnSet) {
            HashSet<String> strs = first.get(key);
            System.out.print(key + "\t:\t");
            for (String str : strs) {
                System.out.print(str + "\t");
            }
            System.out.println();
        }
        System.out.println("----------------------------------------first----------------------------------------");
        System.out.println("----------------------------------------follower----------------------------------------");
        for (String key : VnSet) {
            if (follower.containsKey(key)) {
                HashSet<String> strs = follower.get(key);
                System.out.print(key + "\t:\t");
                for (String str : strs) {
                    System.out.print(str + "\t");
                }
                System.out.println();
            }
        }
        System.out.println("----------------------------------------follower----------------------------------------");
        System.out.println("----------------------------------------分析表----------------------------------------");
        for (int i = 0; i < VnSet.size() + 1; i++) {
            for (int j = 0; j < VtSet.size() + 1; j++) {
                System.out.printf("%8s", "  " + analysis_table[i][j]);
            }
            System.out.println();
        }
        System.out.println("----------------------------------------分析表----------------------------------------");

    }

    public static void main(String[] args) {
        long start = System.currentTimeMillis();
        getVnVt();
        Init();
        printAll();
        analysis();
        long end = System.currentTimeMillis();
        System.out.println("运行时间：" + (end - start) + "ms");
    }
}