package com.json;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Iterator;

import junit.framework.TestCase;

import org.json.JSONException;
import org.json.JSONObject;

/**
 * @author hwl
 *
 */
public class JSONOpe extends TestCase{
	//当前json对象
	private JSONObject curobj;
	//命令 第一个参数
	private String commandFirst = "";
	//命令第二个参数
	private String commandSecond = "";
	//控制是否退出 
	private boolean quitFlag = false;
	
	/**
	 * 查看目录
	 */
	public void getls(){
		Iterator ite = curobj.keys();
		while(ite.hasNext()){
			System.out.println(ite.next().toString());
		}
	}
	/**
	 * 进入到某个目录下
	 * @param obj
	 * @param path
	 * @param flag
	 */
	public void getcd(JSONObject obj,String path,boolean flag){
		if(!flag){
			flag = obj.has(path);
			if(flag)
				try {
					curobj = (JSONObject) obj.get(path);
				} catch (JSONException e) {
					//e.printStackTrace();
					System.out.println("cast error!");
				}
			else{
				Iterator ite = obj.keys();
				while(ite.hasNext()){
					String key = ite.next().toString();
					try {
						obj = (JSONObject) obj.get(key);
						getcd(obj,path,flag);
					} catch (JSONException e) {
						//e.printStackTrace();
						System.out.println("json is end!");
					}
				}
			}
		}
	}
	/**
	 * 查看信息
	 * @param key
	 */
	public void getcat(String key){
		Iterator ite = curobj.keys();
		while(ite.hasNext()){
			String temp = ite.next().toString();
			if(temp.equals(key)){
				JSONObject o;
				try {
					o = (JSONObject) curobj.get(key);
					System.out.println(o);
				} catch (JSONException e) {
					e.printStackTrace();
				}
				
			}
		}
	}
	/**
	 * 增加命令
	 */
	public void getadd(){
		System.out.println("key:");
		String key = "";
		key = getfromConsole();
		System.out.println("value:");
		String value = "";
		value = getfromConsole();
		try {
			JSONObject temp = new JSONObject(value);
			System.out.println("add success!");
			curobj.put(key, temp);
		} catch (JSONException e) {
			//e.printStackTrace();
			System.out.println("the format is wrong!try again");
		}finally{
		}
		
	}
	/**
	 * 删除命令
	 */
	public void getremove(){
		System.out.println("please give the key:");
		String key = "";
		key = getfromConsole();//接收关键字key
		curobj.remove(key);
		System.out.println(key+" was deleted from JSON");
	}
	/**
	 * 从控制台读入命令 
	 * @return
	 */
	public String getfromConsole(){
		String line = "";
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in)); 
		try {
			line = br.readLine();
		} catch (IOException e) {
			e.printStackTrace();
		}
		return line;
	}
	/**
	 * 分析命令
	 * @return
	 */
	private int readString() {
        int com = 0;
        String line = null;
        line = getfromConsole();
        if("".equals(line)){
        	return com;
        }
		String s[] = line.split(" ");
    	if(s.length>0&&s.length<3){
    		//看第一个参数
    		String s0 = s[0];
    		if("ls".equals(s0)){
    			com = 1;
    		}else if("cd".endsWith(s0)){
    			com = 2;
    			commandSecond = s[1];//第二个参数
    		}else if("cat".equals(s0)){
    			com = 3;
    			commandSecond = s[1];
    		}else if("add".equals(s0)){
    			com = 4;
    		}else if("remove".equals(s0)){
    			com = 5;
    		}else if("!help".equals(s0)){
    			com = 6;
    		}else if("!quit".equals(s0)){
    			com = 7;
    		}else{
    			return com;
    		}
    	}else{
    		return com;
    	}
		return com;
    } 
	/**
	 * 帮助命令
	 */
	public void gethelp(){
		StringBuffer sb = new StringBuffer();
		sb.append("ls :command to list the items in current position\n");
		sb.append("cd :command to go to the entry like go to a directory\n");
		sb.append("cat :command to display th item data\n");
		sb.append("add :command to add new address entry to JSON\n");
		sb.append("remove :command to remove one or more address entries\n");
		sb.append("!help :get help\n");
		sb.append("!quit :quit from the application");
		System.out.println(sb.toString());
	}
	/**
	 * 退出命令
	 * @param test
	 */
	public void getquit(JSONOpe test){
		test.setQuitFlag(false);
		System.out.println("quited!");
	}
	/**
	 * 程序入口
	 * @param args
	 * @throws JSONException
	 */
	public static void main(String[] args) throws JSONException {
		String sjson = "{\"entries\": {\"lilei\" : {\"age\": 27,\"mobile\" : \"13700000000\",\"address\" : \"Earth somewhere\"}, \"hanmeimei\" : {\"age\": 26,\"mobile\" : \"13700000001\",\"address\" : \"Earth somewhere else\"}}}";
		JSONOpe jsonOpe = new JSONOpe();
		JSONObject root = new JSONObject(sjson);
		JSONObject curobj = root;
		jsonOpe.setCurobj(curobj);
		jsonOpe.setQuitFlag(true);
		//循环输入信息
		while(jsonOpe.isQuitFlag()){
			int n = 0;
			n = jsonOpe.readString();
			switch(n){
			    case 0:System.out.println("input error!type \"!help\" for help\"");break;
				case 1:jsonOpe.getls();break;
				case 2:{
					boolean flag = false;//每次查询都重置标志位
					curobj = root;
					jsonOpe.getcd(curobj,jsonOpe.getCommandSecond(),flag);break;
				}
				case 3:jsonOpe.getcat(jsonOpe.getCommandSecond());break;
				case 4:jsonOpe.getadd();break;
				case 5:jsonOpe.getremove();break;
				case 6:jsonOpe.gethelp();break;
				case 7:jsonOpe.getquit(jsonOpe);break;
				default:break;
			}
		}
	}
	public JSONObject getCurobj() {
		return curobj;
	}
	public void setCurobj(JSONObject curobj) {
		this.curobj = curobj;
	}
	public String getCommandFirst() {
		return commandFirst;
	}
	public void setCommandFirst(String commandFirst) {
		this.commandFirst = commandFirst;
	}
	public String getCommandSecond() {
		return commandSecond;
	}
	public void setCommandSecond(String commandSecond) {
		this.commandSecond = commandSecond;
	}
	public boolean isQuitFlag() {
		return quitFlag;
	}
	public void setQuitFlag(boolean quitFlag) {
		this.quitFlag = quitFlag;
	}
}
