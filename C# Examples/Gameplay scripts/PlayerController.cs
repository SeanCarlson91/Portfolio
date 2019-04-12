using UnityEngine;
using System.Collections;

public class PlayerController : MonoBehaviour {

	public float speed;
	public float jump;
	float moveVelocity;
	bool grounded = false;

	void Update () {

		//Jump
		if (Input.GetKeyDown(KeyCode.Space)) {
			if (grounded) {
				GetComponent<Rigidbody2D> ().velocity = new Vector2 (
					GetComponent<Rigidbody2D>().velocity.x, jump);
			}
		}

		//Horizontal Movement
		if (Input.GetKey(KeyCode.A)){
			
				moveVelocity = -speed;
			
		}
		if (Input.GetKey(KeyCode.D)){
			
				moveVelocity = speed;

		}

		GetComponent<Rigidbody2D> ().velocity = new Vector2 (moveVelocity, 
			GetComponent<Rigidbody2D> ().velocity.y);
	}

	void OnTriggerEnter2D(){
		grounded = true;
	}

	void OnTriggerExit2D(){
		grounded = false;
	}
}
