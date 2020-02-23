package com.git.service;

import com.git.domain.Account;

import java.util.List;

/**
 * @author ashen
 *	业务层的接口
 */
public interface IAccountService {
	
	void saveAccount(Account account);
	
	void deleteAccount(Integer id);
	
	void updateAccount(Account account);

	List<Account> findAllAccount();
	
	Account findAccountById(Integer id);

	void transferAccount(String outName, String inName, float money);
		
}
