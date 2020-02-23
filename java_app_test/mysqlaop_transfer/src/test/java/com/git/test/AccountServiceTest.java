package com.git.test;

import com.git.domain.Account;
import com.git.service.IAccountService;
import org.junit.Test;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

import java.util.List;


public class AccountServiceTest {
	@Test
	public void testFindAll() {
		// 1. 获取容器
		ApplicationContext ac = new ClassPathXmlApplicationContext("bean.xml");
		// 2. 业务层对象
		IAccountService ias = ac.getBean("accountService", IAccountService.class);
		List<Account> accounts = ias.findAllAccount();
		for (Account ac1 : accounts) {
			System.out.println(ac1.toString());
		}
	}

	@Test
	public void testTransferAccount() {
		// 1. 获取容器
		ApplicationContext ac = new ClassPathXmlApplicationContext("bean.xml");
		// 2. 业务层对象
		IAccountService ias = ac.getBean("accountService", IAccountService.class);
		ias.transferAccount("aaa", "bbb", 1f);
	}
}
