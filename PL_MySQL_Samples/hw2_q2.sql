ACCEPT p_1 PROMPT 'Please enter a Department Name:'

DECLARE
v_deprt_name department.department_name%TYPE := '&p_1';
v_deprt_id   department.department_id%TYPE;
v_address         department.address%TYPE;
v_emply_count     NUMBER;
v_avg_salary      employee.salary%TYPE;
v_emply_count2    NUMBER;
v_emply_count3    NUMBER;
v_temp            NUMBER;

BEGIN
  DBMS_OUTPUT.PUT_LINE('User Input:');
  DBMS_OUTPUT.PUT_LINE(v_deprt_name);
  DBMS_OUTPUT.PUT_LINE('My Output:');
  
  SELECT COUNT(*)
    INTO v_temp
    FROM department
    WHERE UPPER(department_name) = UPPER(v_deprt_name);
  
  IF v_temp != 1 THEN
    DBMS_OUTPUT.PUT_LINE(v_deprt_name || ' is not in the Department Table');
  ELSE
    SELECT department_id, address
      INTO v_deprt_id, v_address
      FROM department
      WHERE UPPER(department_name) = UPPER(v_deprt_name);
  
    DBMS_OUTPUT.PUT_LINE('Department Name: ' || UPPER(v_deprt_name));
    DBMS_OUTPUT.PUT_LINE('a) ' || TO_CHAR(v_deprt_id));
    DBMS_OUTPUT.PUT_LINE('b) ' || TO_CHAR(v_address));
    
    SELECT COUNT(*), AVG(salary)
      INTO v_emply_count, v_avg_salary
      FROM employee
      WHERE department_id = v_deprt_id;
      
    DBMS_OUTPUT.PUT_LINE('c) ' || TO_CHAR(v_emply_count));
    DBMS_OUTPUT.PUT_LINE('d) ' || TRIM(TO_CHAR(NVL(v_avg_salary, 0), '$99,990.00')));
    
    SELECT COUNT(*) 
      INTO v_emply_count2
      FROM employee
      WHERE department_id = v_deprt_id
      AND salary < v_avg_salary;
      
    DBMS_OUTPUT.PUT_LINE('e) ' || TO_CHAR(v_emply_count2));
    
    SELECT COUNT(*)
      INTO v_emply_count3
      FROM employee
      WHERE  department_id = v_deprt_id
      AND    salary < (SELECT AVG(salary) FROM   employee);
    
    DBMS_OUTPUT.PUT_LINE('f) ' || TO_CHAR(v_emply_count3)); 
  END IF;
END;