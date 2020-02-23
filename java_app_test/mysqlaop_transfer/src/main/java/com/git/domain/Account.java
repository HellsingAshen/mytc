package com.git.domain;

import java.io.Serializable;

public class Account implements Serializable {
	private Integer	id;
	private String	name;
	private float	money;
	
	public Integer getId() {
		return id;
	}
	public void setId(Integer id) {
		this.id = id;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public float getMoney() {
		return money;
	}
	public void setMoney(float money) {
		this.money = money;
	}
	@Override
	public String toString()
	{
		return "Account :{ name " +this.name + " Money : " + this.money + " }" ;
	}
}
