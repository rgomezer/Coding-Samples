DECLARE    
  v_avg80        employee.salary%TYPE;
  v_num_emply_dept  NUMBER;
  v_output       varchar2(1000);
  CURSOR c_dept IS
        SELECT   	d.department_id, d.department_name, e.avg_salary
        FROM 	  	department d
        INNER JOIN (SELECT department_id, COUNT(*), AVG(salary) AS avg_salary
                    FROM employee
                    GROUP BY department_id
                    HAVING COUNT(*) > 2
                    AND department_id IS NOT NULL) e
        ON d.department_id = e.department_id
        ORDER BY department_id;
  CURSOR c_emp (p_dept_id NUMBER, p_avg_sal NUMBER) IS
        SELECT employee_name, salary
          FROM employee
         WHERE department_id = p_dept_id
           AND salary > p_avg_sal
         ORDER BY employee_name;
BEGIN 
  FOR i IN c_dept LOOP
    v_avg80 := i.avg_salary * 0.8;
    SELECT COUNT(*)
      INTO v_num_emply_dept
      FROM employee
     WHERE department_id = i.department_id
       AND salary > i.avg_salary * 0.8;
    IF v_num_emply_dept > 0 THEN      
      DBMS_OUTPUT.PUT_LINE(RPAD('DEPARTMENT ID:', 26) || i.department_id);
      DBMS_OUTPUT.PUT_LINE(RPAD('DEPARTMENT NAME:', 26) || i.department_name);
      DBMS_OUTPUT.PUT_LINE(RPAD('AVERAGE SALARY:', 24) || TO_CHAR(i.avg_salary, '$99,990.00'));  
      DBMS_OUTPUT.PUT_LINE(RPAD('80% OF AVERAGE SALARY:', 24) || TO_CHAR(v_avg80, '$99,990.00'));
      DBMS_OUTPUT.PUT_LINE('There are ' || TO_CHAR(v_num_emply_dept) || ' employees whose salaries are above ' || TRIM(TO_CHAR(v_avg80, '$99,990.00')) || '.');
      v_output := '';
      FOR j IN c_emp(i.department_id, v_avg80) LOOP
        v_output := v_output || j.employee_name || ' ' ||	TRIM(TO_CHAR(ROUND(j.salary, 2), '$99,990.00')) || '; ';	        
      END LOOP;
      DBMS_OUTPUT.PUT_LINE('EMPLOYEE NAME AND SALARY: ' || v_output);
      DBMS_OUTPUT.PUT_LINE('');
    END IF;
  END LOOP;  
END;