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
	//��ǰjson����
	private JSONObject curobj;
	//���� ��һ������
	private String commandFirst = "";
	//����ڶ�������
	private String commandSecond = "";
	//�����Ƿ��˳� 
	private boolean quitFlag = false;
	
	/**
	 * �鿴Ŀ¼
	 */
	public void getls(){
		Iterator ite = curobj.keys();
		while(ite.hasNext()){
			System.out.println(ite.next().toString());
		}
	}
	/**
	 * ���뵽ĳ��Ŀ¼��
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
	 * �鿴��Ϣ
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
	 * ��������
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
	 * ɾ������
	 */
	public void getremove(){
		System.out.println("please give the key:");
		String key = "";
		key = getfromConsole();//���չؼ���key
		curobj.remove(key);
		System.out.println(key+" was deleted from JSON");
	}
	/**
	 * �ӿ���̨�������� 
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
	 * ��������
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
    		//����һ������
    		String s0 = s[0];
    		if("ls".equals(s0)){
    			com = 1;
    		}else if("cd".endsWith(s0)){
    			com = 2;
    			commandSecond = s[1];//�ڶ�������
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
	 * ��������
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
	 * �˳�����
	 * @param test
	 */
	public void getquit(JSONOpe test){
		test.setQuitFlag(false);
		System.out.println("quited!");
	}
	/**
	 * �������
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
		//ѭ��������Ϣ
		while(jsonOpe.isQuitFlag()){
			int n = 0;
			n = jsonOpe.readString();
			switch(n){
			    case 0:System.out.println("input error!type \"!help\" for help\"");break;
				case 1:jsonOpe.getls();break;
				case 2:{
					boolean flag = false;//ÿ�β�ѯ�����ñ�־λ
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
